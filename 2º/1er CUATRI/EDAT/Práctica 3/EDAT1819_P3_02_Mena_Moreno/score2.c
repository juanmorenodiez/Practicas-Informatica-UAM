#include <stdio.h>
#include "type.h"
#include "table.h"
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "index.h"

int main(int argc, char **argv) {
  SQLHENV env;
  SQLHDBC dbc;
  SQLHSTMT stmt;
  SQLRETURN ret; /* ODBC API return status */
  char query[256];
  long long userid;
  int FLAG=0;   /*to  check username exists*/

  /*Error management*/
  if (argc<4) {
    fprintf(stderr, "Not enough params.\nFormat must be: ./score2 <scrname> <score> ''<comment>''\n");
    exit(0);
  }

  if (argc>5) {
    fprintf(stderr, "Too many params.\nFormat must be: ./score2 <scrname> <score> ''<comment>''\n");
    exit(0);
  }

  /*Store the introduced score in a variable*/
  int score = atoi(argv[2]);
  if (score<1 || score>100) {
    fprintf(stderr, "Score must be between 1 and 100\n");
    exit(0);
  }


  /*Process of connecting to database and getting the user id*/
  /*custom view we want to create*/
  sprintf (query, "create view name_to_id as select user_id from users where screenname='%s'", argv[1]);

  /* CONNECT */
  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return EXIT_FAILURE;
  }

  /* Allocate a statement handle */
  SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);


  /*droping view in case it existed*/
  SQLExecDirect(stmt, (SQLCHAR*) "drop view name_to_id cascade;", SQL_NTS);
  SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

  /*Check that the user exists*/
  SQLExecDirect(stmt, (SQLCHAR*) "select user_id from name_to_id", SQL_NTS);

  /* Getting the id the user introduces, and checking if it exists */
  if (SQL_SUCCEEDED(ret = SQLFetch(stmt))){
      ret = SQLGetData(stmt, 1, SQL_C_SBIGINT, &userid, sizeof(userid), NULL);
      FLAG=1;
  }

  if (FLAG==0){
    printf ("There isn't any username with the name %s\n", argv[1]);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret))
      return EXIT_FAILURE;

    return 0;
  }

  /* free up statement handle */
  SQLFreeHandle(SQL_HANDLE_STMT, stmt);

  /* DISCONNECT */
  ret = odbc_disconnect(env, dbc);
  if (!SQL_SUCCEEDED(ret))
    return EXIT_FAILURE;

  /*We start to insert the information in our files*/
  char tablename1[16]="data_index.dat";
  char tablename2[16]="data_table.dat";
  int ncols = 4;
  type_t types[] = {LLNG, STR, INT, STR};

  FILE *fp=fopen (tablename1, "r");
  if (fp==NULL)
    index_create(INT, tablename1);
  else
    fclose(fp);

  index_t *index = index_open(tablename1);
  if (index == NULL)
      return -1;

  table_t *tb;
  if ((tb=table_open(tablename2))==NULL) {
    table_create(tablename2, ncols, types);
    tb = table_open(tablename2);

    if (!tb){
      fprintf(stderr, "Created table, but can't open it back (%s).\n", tablename2);
      exit(0);
    }
  }

  void **q = (void **) malloc(ncols*sizeof(void *));
  q[0] = &userid;
  q[1] = argv[1];
  q[2] = &score;
  q[3] = argv[3];

  void **buff = (void **) malloc(ncols * sizeof(void *));
  if(buff==NULL){
    printf ("Unable to allocate memory\n");
    exit (0);
  }

  /*Checking if the user already has a score*/
  char *screenname;
  long pos = table_first_pos(tb);
  int r=0;
  while(pos < table_last_pos(tb)){
      pos = table_read_record(tb, pos);

      r++;
      for(int i=0; i < table_ncols(tb); i++) { /* Reading everything */
          buff[i] = table_column_get(tb, i);
      }
      screenname = (char *)buff[1];
      if (strcmp(screenname, argv[1])==0){
        fprintf(stderr, "There is already a score for user %s\n", argv[1]);
        index_close(index);
        table_close(tb);
        free (buff);
        return -1;
      }
  }

  table_insert_record(tb, q);
  index_put(index, score, table_last_pos (tb));
  fprintf(stdout, "Everything working just as expected, user and information inserte correctly.\n");
  table_close(tb);
  index_save(index);
  index_close(index);
  free(q);
  free(buff);
  return 0;
}

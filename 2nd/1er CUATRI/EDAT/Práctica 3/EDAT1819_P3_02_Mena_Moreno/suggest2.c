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
  SQLSMALLINT columns; /* number of columns in result-set */
  SQLINTEGER x;
  SQLCHAR y[512];
  long long userid;
  char query[256];
  int ncols = 4;
  int flag = 0; /*To check there is at least a user with score over the given*/
  int original_score=-1;
  /*Error management*/
  if (argc<2) {
    fprintf(stderr, "Not enough params.\nFormat must be: ./suggest <score>\n");
    exit(0);
  }

  if (argc>2) {
    fprintf(stderr, "Too many params.\nFormat must be: ./suggest <score>\n");
    exit(0);
  }

  /*Store the introduced score in a variable*/
  int score = atoi(argv[1]);
  if (score<1 || score>99) {
    fprintf(stderr, "Score must be between 1 and 100\n");
    exit(0);
  }
  original_score=score;

  /*Users need to have score +1 or more*/
  score+=1;

  /* CONNECT */
  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return EXIT_FAILURE;
  }

  /*File from where we want to read*/
  char tablename1[16]="data_index.dat";
  char tablename2[16]="data_table.dat";

  /*Allocate memory for reading the file information*/
  void **buff = (void **) malloc(ncols * sizeof(void *));
  if(buff==NULL){
    printf ("Unable to allocate memory\n");
    exit (0);
  }


  index_t *index = index_open(tablename1);
  if (index == NULL){
    free (buff);
    printf("Could not open index with name %s\n", tablename1);
    return -1;
  }

  table_t *tb = table_open(tablename2);
  if (tb == NULL){
    index_close(index);
    free (buff);
    printf("Could not open the table with name %s\n", tablename2);
    exit (0);
  }
  int poss=0;
  long *aux;

  char *screenname;
  int user_score;
  char *text;
  while (score<=100){
    aux=index_get(index, score, &poss);
    if (aux!=NULL){
      flag = 1;
      for (int i=0; i<poss; i++){

        table_read_record(tb, aux[i]);
        for(int i=0; i < table_ncols(tb); i++) { /* Reading everything */
          buff[i] = table_column_get(tb, i);
        }

        userid = *((long long *)buff[0]);
        screenname = (char *)buff[1];
        user_score = *((int *)buff[2]);
        text = (char *)buff[3];
        printf("%s\t%d\n%s\n\n",screenname, user_score, text);

        /* Allocate a statement handle */
        SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
        /*custom view we want to create*/

        /*custom view we want to create*/
        sprintf (query, "select count(*) from tweets where userwriter=%lld;", userid);

        SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        /* How many columns are there */
        SQLNumResultCols(stmt, &columns);

        /* print the name of each column */
        for (i = 1; i <= columns; i++) {
          SQLCHAR buf[512];
          SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
          printf("Number of tweets:");
        }

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
          ret = SQLGetData(stmt, 1, SQL_C_SLONG, &x, sizeof(SQLINTEGER), NULL);
          printf("%d\n", x);
        }
        /* free up statement handle */
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);

        /* Allocate a statement handle */
        SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

        /*custom view we want to create*/
        sprintf (query, "select tweettext from tweets where userwriter=%lld order by tweettimestamp desc;", userid);
        /* final query giving the required information about the tweets of the user introduced */
        SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
          ret = SQLGetData(stmt, 1, SQL_C_CHAR, y, sizeof(y), NULL);
          printf("%s\n", y);
        }

        /* free up statement handle */
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        printf ("\n\n");
      }
    }
    score+=1;
  }

  if (flag==0){
    printf ("There isn't any user with score over %d, try again.\n", original_score);
    table_close(tb);
    free (buff);
    return -1;
  }

  /* DISCONNECT */
  ret = odbc_disconnect(env, dbc);
  if (!SQL_SUCCEEDED(ret)) {
    index_close(index);
    table_close(tb);
    free (buff);
    return EXIT_FAILURE;
  }

  table_close(tb);
  index_close(index);
  free (buff);
  return 0;
}

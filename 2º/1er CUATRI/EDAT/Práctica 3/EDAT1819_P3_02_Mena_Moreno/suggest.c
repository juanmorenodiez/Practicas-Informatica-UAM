#include <stdio.h>
#include "type.h"
#include "table.h"
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

int main(int argc, char **argv) {
  SQLHENV env;
  SQLHDBC dbc;
  SQLHSTMT stmt;
  SQLRETURN ret; /* ODBC API return status */
  SQLSMALLINT columns; /* number of columns in result-set */
  SQLUSMALLINT i;
  SQLINTEGER x;
  SQLCHAR y[512];
  long long userid;
  char query[256];
  int ncols = 4;
  int flag = 0; /*To check there is at least a user with score over the given*/

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
  if (score<1 || score>100) {
    fprintf(stderr, "Score must be between 1 and 100\n");
    exit(0);
  }

  /* CONNECT */
  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return EXIT_FAILURE;
  }

  /*File from where we want to read*/
  char tablename[10]="data.dat";

  /*Allocate memory for reading the file information*/
  void **buff = (void **) malloc(ncols * sizeof(void *));
  if(buff==NULL){
    printf ("Unable to allocate memory\n");
    exit (0);
  }


  /*Open the table*/
  table_t *tb = table_open(tablename);
  if (tb == NULL){
    printf("Could not open the table with name %s\n", tablename);
    free (buff);
    exit (0);
  }

  long pos = table_first_pos(tb);
  char *screenname;
  int user_score;
  char *text;

  /*Read every record, if the score is greater that the given, print*/
  while(pos < table_last_pos(tb)){
      pos = table_read_record(tb, pos);

      for(int i=0; i < table_ncols(tb); i++) { /* Reading everything */
          buff[i] = table_column_get(tb, i);
      }

      userid = *(long long *)buff[0];
      screenname = (char *)buff[1];
      user_score = *(int *)buff[2];
      text = (char *)buff[3];
      if (user_score > score){
        flag = 1;
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

  if (flag==0){
    printf ("There isn't any user with score over %d, try again.\n", score);
    table_close(tb);
    free (buff);
    return -1;
  }

  /* DISCONNECT */
  ret = odbc_disconnect(env, dbc);
  if (!SQL_SUCCEEDED(ret)) {
    table_close(tb);
    free (buff);
    return EXIT_FAILURE;
  }

  table_close(tb);
  free (buff);
  return 0;
}

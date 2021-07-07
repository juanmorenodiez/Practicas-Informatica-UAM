#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int query9(char *tweetid){
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    int FLAG=0;
	char query1[512];
  char query2[512];

  sprintf (query1, "select * from tweets where tweet_id =%s", tweetid);

  /* we need to delete from both the tweet and retweet, in case somebody retweeted that tweet*/
	sprintf (query2, "delete from tweets where tweet_id=%s or retweet=%s", tweetid, tweetid);


    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) query1, SQL_NTS);
    /* How many columns are there */


    /* See if there is any tweet with the provided id */
    if (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
        FLAG=1;

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (FLAG==0){
      printf ("There wasn't any tweet with the id %s\n", tweetid);
      return 0;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) query2, SQL_NTS);
    printf ("Tweet (and their retweets) were deleted correctly\n");

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

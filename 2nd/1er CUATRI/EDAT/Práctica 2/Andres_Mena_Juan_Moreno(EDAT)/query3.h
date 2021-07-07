#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int query3(char *tweetid){
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLSMALLINT columns; /* number of columns in result-set */
    SQLUSMALLINT i;
    SQLINTEGER x;
    SQLCHAR y[512];
    SQLCHAR y1[512];
    SQLCHAR y2[512];
	long long x1;
    int FLAG=0;
    char query1[512];
    char query2[512];
    char check[512];

    sprintf (query1, "select count(*) as number_retweets from tweets where retweet = %s", tweetid);
    sprintf (query2, "select tweet_id, screenname, tweettimestamp, tweettext from tweets as t, users as u where retweet = %s and u.user_id=t.userwriter order by tweettimestamp desc;", tweetid);
    sprintf (check, "select tweet_id from tweets where tweet_id=%s", tweetid);

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }


    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) check, SQL_NTS);

    /* Getting the id the user introduces */
    if (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
        FLAG=1;

    if (FLAG==0){
      printf ("There isn't any tweet with the id %s\n", tweetid);
      return 0;
    }
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);


    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) query1, SQL_NTS);
    /* How many columns are there */
    SQLNumResultCols(stmt, &columns);


    /*before printing the column, we check if it has 0 retweets to show a different message*/
    if (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        ret = SQLGetData(stmt, 1, SQL_C_SLONG, &x, sizeof(SQLINTEGER), NULL);
        if (x==0){
          printf ("The tweet with id %s has never been retweeted.\n", tweetid);
          return 0;
        }
    }
    /* print the name of each column */
    for (i = 1; i <= columns; i++) {
        SQLCHAR buf[512];
        SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
        printf("%s\t", buf);
    }
    printf(":%d\n\n", x);



    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) query2, SQL_NTS);
    /* How many columns are there */
    SQLNumResultCols(stmt, &columns);

    /* print the name of each column */
    for (i = 1; i <= columns; i++) {
        SQLCHAR buf[512];
        SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
        printf("%s\t\t", buf);
    }
    printf("\n");


    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        ret = SQLGetData(stmt, 1, SQL_C_SBIGINT, &x1, sizeof(x1), NULL);
        ret = SQLGetData(stmt, 2, SQL_C_CHAR, y, sizeof(y), NULL);
        ret = SQLGetData(stmt, 3, SQL_C_CHAR, y1, sizeof(y1), NULL);
        ret = SQLGetData(stmt, 4, SQL_C_CHAR, y2, sizeof(y2), NULL);
        printf("%lld\t\t%s\t\t%s\t\t%s\t\n", x1, y, y1, y2);
    }

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

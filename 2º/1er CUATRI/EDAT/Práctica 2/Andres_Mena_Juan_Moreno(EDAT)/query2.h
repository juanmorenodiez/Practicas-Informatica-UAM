#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int query2(char *username) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLSMALLINT columns; /* number of columns in result-set */
    SQLUSMALLINT i;
    SQLINTEGER x;
    SQLCHAR y[512];
    SQLCHAR y1[512];
	  char query[256];
    int FLAG=0;
    long long tweetid;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }



    sprintf (query, "create view name_to_id as select user_id from users where screenname='%s'", username);


    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple queries creating neccesary views */
    SQLExecDirect(stmt, (SQLCHAR*) "drop view name_to_id cascade;", SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    /*Check that the user exists*/
    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select user_id from name_to_id", SQL_NTS);

    /* Getting the id the user introduces */
    if (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
        FLAG=1;

    if (FLAG==0){
      printf ("There isn't any user with name %s\n", username);
      return 0;
    }
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);


    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select count(*) from tweets, name_to_id as n where userwriter=n.user_id;", SQL_NTS);
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
	  printf ("\n");



    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select tweet_id, tweettimestamp, tweettext from tweets, name_to_id as n where userwriter=n.user_id order by tweettimestamp desc;", SQL_NTS);
    /* How many columns are there */
    SQLNumResultCols(stmt, &columns);

    /* print the name of each column */
    for (i = 1; i <= columns; i++) {
        SQLCHAR buf[512];
        SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
        printf("%s\t\t", buf);
    }
    printf ("\n");


    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        ret = SQLGetData(stmt, 1, SQL_C_SBIGINT, &tweetid, sizeof(tweetid), NULL);
        ret = SQLGetData(stmt, 2, SQL_C_CHAR, y, sizeof(y), NULL);
	      ret = SQLGetData(stmt, 3, SQL_C_CHAR, y1, sizeof(y1), NULL);
        printf("%lld\t%s\t%s\t\n", tweetid, y, y1);
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

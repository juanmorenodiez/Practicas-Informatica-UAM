#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"



int query4() {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLSMALLINT columns; /* number of columns in result-set */
    SQLUSMALLINT i;
    SQLINTEGER x;
    SQLCHAR y[512];
    long long x1;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }


    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLExecDirect(stmt, (SQLCHAR*) "drop view retweets cascade;", SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) "create view retweets as select retweet as retweeted_id, count(*) as number_retweets from tweets where retweet <> 0 group by retweet order by number_retweets desc limit 20;", SQL_NTS);

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select retweeted_id, number_retweets, screenname from users as u, retweets as t1, tweets as t2 where t1.retweeted_id=t2.tweet_id and t2.userwriter=u.user_id", SQL_NTS);
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
        ret = SQLGetData(stmt, 2, SQL_C_SLONG, &x, sizeof(SQLINTEGER), NULL);
        ret = SQLGetData(stmt, 3, SQL_C_CHAR, y, sizeof(y), NULL);
        printf("%lld\t\t%d\t\t%s\n", x1, x, y);
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int query5() {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLSMALLINT columns; /* number of columns in result-set */
    SQLUSMALLINT i;
    long long x;
    SQLINTEGER x1;
    SQLCHAR y[512];


    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }


    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLExecDirect(stmt, (SQLCHAR*) "drop view most_followed cascade;", SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) "create view most_followed as select userfolloweed as max_followed, count(*) as num_followers from follows group by userfolloweed order by num_followers desc limit 20", SQL_NTS);

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select max_followed, screenname, num_followers from users as u1, most_followed as u2 where u1.user_id=u2.max_followed", SQL_NTS);
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
        ret = SQLGetData(stmt, 1, SQL_C_SBIGINT, &x, sizeof(x), NULL);
        ret = SQLGetData(stmt, 2, SQL_C_CHAR, y, sizeof(y), NULL);
        ret = SQLGetData(stmt, 3, SQL_C_SLONG, &x1, sizeof(SQLINTEGER), NULL);
        if (x<10000000)
          printf("%lld\t\t\t%s\t\t\t%d\n", x, y, x1);
        else if (strlen((char *)y)<8 || !strcmp((char *)y, "el_pais"))
          printf("%lld\t\t%s\t\t\t%d\n", x, y, x1);
        else
          printf("%lld\t\t%s\t\t%d\n", x, y, x1);
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

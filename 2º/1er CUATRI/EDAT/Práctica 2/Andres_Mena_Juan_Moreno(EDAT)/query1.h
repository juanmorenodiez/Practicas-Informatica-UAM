#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int query1(char *username) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLSMALLINT columns; /* number of columns in result-set */
    SQLUSMALLINT i;
    SQLINTEGER x;
    SQLCHAR y[512];
	  char query[256];
    int FLAG=0;

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
    SQLExecDirect(stmt, (SQLCHAR*) "drop view ids_followeed cascade;", SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) "drop view ids_followers cascade;", SQL_NTS);

    SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

    SQLExecDirect(stmt, (SQLCHAR*) "create view ids_followeed as select userfolloweed from follows, name_to_id as n where userfollower=n.user_id;", SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) "create view ids_followers as select userfollower from follows, name_to_id as n where userfolloweed=n.user_id;", SQL_NTS);


    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);


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
    SQLExecDirect(stmt, (SQLCHAR*) "select count(*) as number_of_users_following from ids_followeed", SQL_NTS);
    /* How many columns are there */
    SQLNumResultCols(stmt, &columns);

    /* print the name of each column */
    for (i = 1; i <= columns; i++) {
        SQLCHAR buf[512];
        SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
        printf("%s", buf);
    }
    printf(": ");

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        ret = SQLGetData(stmt, 1, SQL_C_SLONG, &x, sizeof(SQLINTEGER), NULL);
        printf("%d\n", x);
    }
	  printf ("\n");


    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select screenname as followings_list from ids_followeed as a1, users as a2 where a1.userfolloweed=a2.user_id;", SQL_NTS);
    /* How many columns are there */
    SQLNumResultCols(stmt, &columns);

    /* print the name of each column */
    for (i = 1; i <= columns; i++) {
        SQLCHAR buf[512];
        SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
        printf("%s\t", buf);
    }
    printf(":\n");


    SQLBindCol(stmt, 1, SQL_C_CHAR, y, sizeof(y), NULL);
    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("%s\n", y);
    }

    printf ("\n\n");

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select count(*) as number_of_followers from ids_followers", SQL_NTS);
    /* How many columns are there */
    SQLNumResultCols(stmt, &columns);

    /* print the name of each column */
    for (i = 1; i <= columns; i++) {
        SQLCHAR buf[512];
        SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
        printf("%s", buf);
    }
    printf(": ");

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        ret = SQLGetData(stmt, 1, SQL_C_SLONG, &x, sizeof(SQLINTEGER), NULL);
        printf("%d\n", x);
    }
	  printf ("\n");


    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select screenname as followers_list from ids_followers as a1, users as a2 where a1.userfollower=a2.user_id;", SQL_NTS);
    /* How many columns are there */
    SQLNumResultCols(stmt, &columns);

    /* print the name of each column */
    for (i = 1; i <= columns; i++) {
        SQLCHAR buf[512];
        SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
        printf("%s\t", buf);
    }
    printf(":\n");


    SQLBindCol(stmt, 1, SQL_C_CHAR, y, sizeof(y), NULL);
    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("%s\n", y);
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

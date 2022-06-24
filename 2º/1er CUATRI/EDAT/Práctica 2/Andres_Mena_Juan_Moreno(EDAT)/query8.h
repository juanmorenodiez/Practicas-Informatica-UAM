#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int query8(char *username, char *tweettext) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
	  char query1[256];
    char query2[256];
    long long userid;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    sprintf (query1, "create view name_to_id as select user_id from users where screenname='%s'", username);

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple queries creating neccesary views */
    SQLExecDirect(stmt, (SQLCHAR*) "drop view name_to_id cascade;", SQL_NTS);

    SQLExecDirect(stmt, (SQLCHAR*) query1, SQL_NTS);

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);




    /*We check if the user exists*/
    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select user_id from name_to_id", SQL_NTS);

    /* Getting the id the user introduces */
    if (!SQL_SUCCEEDED(ret = SQLFetch(stmt))){
        printf ("The user %s does not exist, so it cannot tweet anything.\n", username);
        return 0;
    }
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);






    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select user_id from name_to_id", SQL_NTS);

    /* Getting the id the user introduces */
    if (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
        ret = SQLGetData(stmt, 1, SQL_C_SBIGINT, &userid, sizeof(userid), NULL);


    sprintf (query2, "insert into tweets (tweettext, tweettimestamp, userwriter) values ('%s', now(), %lld) ", tweettext, userid);

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) query2, SQL_NTS);
    /* How many columns are there */

    printf ("Tweet inserted correctly\n");

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

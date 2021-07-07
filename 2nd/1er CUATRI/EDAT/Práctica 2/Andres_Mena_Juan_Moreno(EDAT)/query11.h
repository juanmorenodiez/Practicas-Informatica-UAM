#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int query11(char *username1, char *username2) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
	  char query1[256];
    char query2[256];
    char query3[256];
    char check[256];
    long long userid1;
    long long userid2;
    int FLAG=0;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    sprintf (query1, "create view name_to_id1 as select user_id from users where screenname='%s';", username1);
    sprintf (query2, "create view name_to_id2 as select user_id from users where screenname='%s';", username2);


    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple queries creating neccesary views */
    SQLExecDirect(stmt, (SQLCHAR*) "drop view name_to_id1 cascade;", SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) "drop view name_to_id2 cascade;", SQL_NTS);

    SQLExecDirect(stmt, (SQLCHAR*) query1, SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) query2, SQL_NTS);

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);


    /*Check that there is a tweet with the id specified*/
    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */

    SQLExecDirect(stmt, (SQLCHAR*) "select user_id from name_to_id2", SQL_NTS);

    /* Getting the id the user introduces */
    if (SQL_SUCCEEDED(ret = SQLFetch(stmt))){
        ret = SQLGetData(stmt, 1, SQL_C_SBIGINT, &userid2, sizeof(userid2), NULL);
        FLAG=1;
    }


    if (FLAG==0){
      printf ("There isn't any user with the name %s\n", username2);
      return 0;
    }
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);


    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */

    SQLExecDirect(stmt, (SQLCHAR*) "select user_id from name_to_id1", SQL_NTS);
    FLAG=0;
    /* Getting the id the user introduces */
    if (SQL_SUCCEEDED(ret = SQLFetch(stmt))){
        ret = SQLGetData(stmt, 1, SQL_C_SBIGINT, &userid1, sizeof(userid1), NULL);
        FLAG=1;
    }


    if (FLAG==0){
      printf ("There isn't any user with the name %s\n", username1);
      return 0;
    }
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);


    /*Check if user1 y already following user2*/
    sprintf (check, "select * from follows where userfollower=%lld and userfolloweed=%lld", userid1, userid2);
    SQLExecDirect(stmt, (SQLCHAR*) check, SQL_NTS);

    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf ("User %s is already following user %s\n", username1, username2);
      return 0;
    }

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);


    sprintf (query3, "insert into follows (userfollower, userfolloweed) values (%lld, %lld);", userid1, userid2);
    SQLExecDirect(stmt, (SQLCHAR*) query3, SQL_NTS);
    printf ("Done correctly!\n");
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

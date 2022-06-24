#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int query7(char *username){
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    int FLAG=0;
	char query1[512];
  char delete1[512];
  char delete2[512];
  char delete3[512];
  long long userid;



  sprintf (query1, "create view name_to_id as select user_id from users where screenname='%s'", username);


    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "drop view name_to_id cascade;", SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) query1, SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) "select user_id from name_to_id", SQL_NTS);

    /* Getting the id the user introduces */
    if (SQL_SUCCEEDED(ret = SQLFetch(stmt))){
        ret = SQLGetData(stmt, 1, SQL_C_SBIGINT, &userid, sizeof(userid), NULL);
        FLAG=1;
    }

    if (FLAG==0){
      printf ("There wasn't any user with the name %s\n", username);
      return 0;
    }

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);


    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    sprintf (delete1, "delete from follows where userfollower=%lld or userfolloweed=%lld;", userid, userid);
    SQLExecDirect(stmt, (SQLCHAR*) delete1, SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    sprintf (delete2, "delete from tweets where userwriter=%lld;", userid);
    SQLExecDirect(stmt, (SQLCHAR*) delete2, SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    sprintf (delete3, "delete from users where user_id=%lld;", userid);
    SQLExecDirect(stmt, (SQLCHAR*) delete3, SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    printf ("User %s deleted correctly\n", username);



    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

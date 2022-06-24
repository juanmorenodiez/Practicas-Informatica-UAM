#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int query10(char *username, char *tweetid) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
	  char query1[256];
    char query2[256];
    char check[256];
    long long userid;
    char text[512];
    int FLAG=0;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    sprintf (query1, "create view name_to_id as select user_id from users where screenname='%s'\n", username);
    sprintf (query2, "create view text_of_tweet as select tweettext from tweets where tweet_id=%s\n", tweetid);


    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple queries creating neccesary views */
    SQLExecDirect(stmt, (SQLCHAR*) "drop view name_to_id cascade;", SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) "drop view text_of_tweet cascade;", SQL_NTS);

    SQLExecDirect(stmt, (SQLCHAR*) query1, SQL_NTS);
    SQLExecDirect(stmt, (SQLCHAR*) query2, SQL_NTS);

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);


    /*Check that there is a tweet with the id specified*/
    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    sprintf (check, "select userwriter from tweets where tweet_id=%s", tweetid);
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
    SQLExecDirect(stmt, (SQLCHAR*) "select user_id from name_to_id", SQL_NTS);

    /* Getting the id the user introduces, and checking if it exists */
	FLAG=0;
    if (SQL_SUCCEEDED(ret = SQLFetch(stmt))){
        ret = SQLGetData(stmt, 1, SQL_C_SBIGINT, &userid, sizeof(userid), NULL);
        FLAG=1;
    }

    if (FLAG==0){
      printf ("There isn't any username with the name %s\n", username);
      return 0;
    }
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLExecDirect(stmt, (SQLCHAR*) "select tweettext from text_of_tweet", SQL_NTS);

    /* Getting the text of the tweet */
    if (SQL_SUCCEEDED(ret = SQLFetch(stmt)))
        ret = SQLGetData(stmt, 1, SQL_C_CHAR, &text, sizeof(text), NULL);


    sprintf (query2, "insert into tweets (tweettext, tweettimestamp, retweet, userwriter) values ('%s', now(), %s, %lld) ", text, tweetid, userid);

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) query2, SQL_NTS);
    /* How many columns are there */

    printf ("Tweet retweeted correctly\n");

    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

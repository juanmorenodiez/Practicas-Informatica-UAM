#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"


int main(int argc, char *argv[]) {

	if (argc > 3){
			printf ("More params than expected\n");
			return 0;
		}
	else if (argc < 2){
		printf ("Not enough params\n");
		return 0;
	}

	if (strcmp(argv[1], "user")==0 && argv[2]!=NULL)
		return query1(argv[2]);

	else if (strcmp(argv[1], "tweets")==0  && argv[2]!=NULL)
		return query2(argv[2]);

	else if (strcmp(argv[1], "retweets")==0  && argv[2]!=NULL)
		return query3(argv[2]);

	else if (strcmp(argv[1], "maxrt")==0 && argv[2]==NULL)
		return query4();

	else if (strcmp(argv[1], "maxfw")==0 && argv[2]==NULL)
		return query5();

	printf ("Incorrect params, try again\n");
	return 0;
}

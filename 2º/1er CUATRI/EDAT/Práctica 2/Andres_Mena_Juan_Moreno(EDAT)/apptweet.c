#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "query8.h"
#include "query9.h"
#include "query10.h"


int main(int argc, char *argv[]) {

	if (argc > 4){
			printf ("More params than expected\n");
			return 0;
		}
	else if (argc < 3){
		printf ("Not enough params\n");
		return 0;
	}

	if (strcmp(argv[1], "new")==0 && argv[2]!=NULL && argv[3]!=NULL)
		return query8(argv[2], argv[3]);

	else if (strcmp(argv[1], "remove")==0 && argv[2]!=NULL && argv[3]==NULL)
		return query9(argv[2]);

	else if (strcmp(argv[1], "retweet")==0 && argv[2]!=NULL && argv[3]!=NULL)
		return query10(argv[2], argv[3]);

	printf ("Incorrect params, try again\n");
	return 0;
}

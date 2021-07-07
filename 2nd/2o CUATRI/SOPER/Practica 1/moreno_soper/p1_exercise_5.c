/* wait and return process info */
#include <sys/types.h>
#include <sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int  main ( void )
{
	pid_t pid;
	char * sentence = (char *)malloc(5 * sizeof (char));
	pid = fork();
	if (pid <  0  )
	{
		printf("Error al emplear fork\n");
		exit (EXIT_FAILURE);
	}
	else  if(pid ==  0)
	{
		strcpy(sentence, "hola");
		free (sentence);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
		printf("Padre: %s\n", sentence);
		free (sentence);
		exit(EXIT_SUCCESS);
	}
}

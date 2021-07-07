/* wait and return process info */
#include <sys/types.h>
#include <sys/wait.h>
/* standard input/output */
#include <stdio.h>
/* malloc, free */
#include <stdlib.h> /* library for exec */
#include <unistd.h>
/*for comparing strings */
#include<string.h>

/*
* Pide al usuario una serie de ficheros separados por comas, los almacena en
* un vector de strings, crea un nuevo proceso y ejecuta el comando cat con el
* vector de strings como vector de argumentos
*/
void  processCat () {

    /* Variables que usa el metodo getline para leer la entrada del usuario */
    char *fileName = NULL;
    size_t fileLen = 0;
    ssize_t fileRead;

    /* pide al usuario una linea de texto con todos los ficheros separados por comas */
    printf("Introduzca los ficheros que quiere mostrar separados por ',' \n");
    while((fileRead = getline(&fileName, &fileLen, stdin)) < 1)
    {
   	 printf("Por favor inserte al menos un fichero \n");
    }

    /* Cuenta el número de ficheros */
    size_t fileCount = 0;
    for(ssize_t i = 0; i < fileRead; i++)
    {
   	 if(fileName[i] == ',' || fileName[i] == '\n')
   	 {
   		 fileCount++;
   	 }
    }

    size_t nArgs = fileCount + 2;
    /* Reserva espacio para argumentos */
    char ** args = malloc(nArgs * sizeof(*args));
    if(args == NULL)
    {
   	 exit(EXIT_FAILURE);
    }

    args[0] = "cat";

    char * filePtr = fileName;
    size_t argIndex = 1;
    for(ssize_t i = 0; i < fileRead; i++)
    {
   	 if(fileName[i] == ',' || fileName[i] == '\n')
   	 {
   		 fileName[i] = '\0';
   		 args[argIndex] = filePtr;
   		 argIndex++;
   		 filePtr = &fileName[i + 1];
   	 }
    }

    args[nArgs - 1] = NULL;

    if (nArgs >  1) {

     /* METER CODIGO
   	 Creamos un nuevo proceso hijo y en el ejecutamos execv para ejecutar el
   	 comando cat con el vector de argumentos args. El padre debe esperar a que
   	 el hijo termine
     */

     int pid = fork();

     if(pid < 0){
       printf("\nError al emplear fork\n");
       exit(EXIT_FAILURE);
     }

     if(pid == 0){
       if((execv("/bin/cat", args)) == -1){
         printf("\n No se pueden leer los archivos");
         exit(EXIT_FAILURE);
       }
     }

     if (pid > 0) {
       wait(NULL);
     }
    }

    /* Liberamos la memoria dinamica reservada por el proceso */
    free (args);
    /* liberamos la memoria reservada por getline */
    free (fileName);
}

void  showAllFiles () {
    /* METER CODIGO */
   /*
    * Creamos un nuevo proceso hijo usando la llamada execlp y en el ejecutamos el
    * comando ls -l. El proceso padre debe de esperar a que el hijo termine.
    */
    int pid = fork();

    if (pid < 0) {
      printf("\nError al emplear fork\n");
      exit(EXIT_FAILURE);
    }

    if (pid == 0) {
      if((execlp("/bin/ls", "ls", "-l", (char *)NULL)) ==-1 ) {
        printf("No se ha podido leer el directorio\n");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_SUCCESS);
    }

    if(pid > 0)
    waitpid(pid, NULL, 0);

}

int  main(void) {
    showAllFiles();
    processCat();
    exit (EXIT_SUCCESS);
}

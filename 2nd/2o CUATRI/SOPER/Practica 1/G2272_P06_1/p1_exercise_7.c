/*
@fichero: p1_exercise_7.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 11/02/2019
@descripción: programa que muestra la información de dos
ficheros separados por ',', previamente ejecuta el comando
ls -l.
*/

/* wait and return process info */
#include <sys/types.h>
#include <sys/wait.h>
/* standard input/output */
#include <stdio.h>
/* malloc, free */
#include <stdlib.h> /* library for exec */
#include <unistd.h>
/*for comparing strings*/
#include<string.h>
#define SIZE 200
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

    /* Cuenta el número de ficheros */
    size_t fileCount = 0;

    /* pide al usuario una linea de texto con todos los ficheros separados por comas */
    printf("Introduzca los ficheros que quiere mostrar separados por ',' \n");
    while((fileRead = getline(&fileName, &fileLen, stdin)) < 1)
    {
   	 printf("Por favor inserte al menos un fichero \n");
    }


    for (ssize_t i = 0; i < fileRead; i++)
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
      int pid = fork();
      if(pid <  0){
        printf("Error al emplear fork\n");
        exit(EXIT_FAILURE);
      }

      if (pid == 0){
        if (execv ("/bin/cat", args) == -1)
          printf ("Error leyendo los archivos\n");
      }

      if (pid>0)
        waitpid(pid, NULL, 0);

     /* METER CODIGO
   	 Creamos un nuevo proceso hijo y en el ejecutamos execv para ejecutar el
   	 comando cat con el vector de argumentos args. El padre debe esperar a que
   	 el hijo termine
     */

    }
    /* Liberamos la memoria dinamica reservada por el proceso */
    free (args);
    /* liberamos la memoria reservada por getline */
    free (fileName);
}

void  showAllFiles () {
  int pid = fork();
  if(pid <  0){
    printf("Error al emplear fork\n");
    exit(EXIT_FAILURE);
  }

  if (pid == 0){
    if ((execlp ("ls", "ls", "-l", (char *)NULL)) == -1){
      printf("No se ha podido leer el directorio\n");
      exit (EXIT_FAILURE);
    }
    exit (EXIT_SUCCESS);
  }

  if (pid>0)
    waitpid (pid, NULL, 0);
}

int  main(void) {
    showAllFiles();
    processCat();
    exit (EXIT_SUCCESS);
}

/*
@fichero: p1_exercise_9.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 18/02/2019
@descripción: programa que trabajará con números aleatorios
leyéndolos e imprimiéndolos mediante el uso de tuberías
y conexiones con los procesos.
*/

 #include <sys/types.h>
 #include <sys/wait.h>
 #include <time.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <unistd.h>

int main(int argc, char *argv[]) {
  int num_escrito, num_leido1, num_leido2, fd[2];

  /* Inicializa el generador con una semilla cualquiera*/
  srand(time(NULL));
  /* Devuelve un numero aleatorio en 0 y MAX_RAND*/
  num_escrito = rand();

  /*creamos una primera tuberia para enlazar padre con un hijo*/
  int pipe_status=pipe(fd);
  if(pipe_status == -1) {
  	perror("Error creando la tuberia 1\n");
  	exit(EXIT_FAILURE);
  }

  /*El padre tiene su primer hijo*/
  int pid = fork();
  if(pid <  0){
    printf("Error al emplear fork\n");
    exit(EXIT_FAILURE);
  }

  /*Si eres el hijo, escribes*/
  if (pid == 0){
    close(fd[0]);
    write(fd[1], &num_escrito, sizeof(int));
    printf("HIJO 1: numero aleatorio %d\n", num_escrito);
    exit(EXIT_SUCCESS);
  }

  /*Aquí solo llegas si eres el padre, que lee*/
  close(fd[1]);
  read(fd[0], &num_leido1, sizeof(int));
  printf ("El padre ha leido %d\n", num_leido1);
  waitpid(pid, NULL, 0);

  /*Creamos la segunda tuberia*/
  pipe_status=pipe(fd);
  if(pipe_status == -1) {
  	perror("Error creando la tuberia 2\n");
  	exit(EXIT_FAILURE);
  }

  /*Creamos el segundo hijo*/
  pid = fork();
  if(pid <  0){
    printf("Error al emplear fork\n");
    exit(EXIT_FAILURE);
  }

  /*Si eres el segundo hijo, lees*/
  else if (pid == 0){
    close (fd[1]);
    read (fd[0], &num_leido2, sizeof(int));
    printf ("HIJO 2: el numero aleatorio recibido es: %d\n", num_leido2);
    exit(EXIT_SUCCESS);
  }

  /*Solo llegas aqui si eres el padre*/
  close(fd[0]);
  write(fd[1], &num_leido1, sizeof(int));
  waitpid(pid, NULL, 0);
  exit(EXIT_SUCCESS);
}

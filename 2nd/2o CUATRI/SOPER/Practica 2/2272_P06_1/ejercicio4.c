/*
@fichero: ejercicio4.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 11/03/2019
@descripción: programa en el que habrá una competición
entre procesos que proporciona un gestor que tratarán
de responder a una señal.Se realizará mediante el envío de
señales a procesos hijo por su padre.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PROC 4

/* manejador_SIGUSR2:*/
void manejador_SIGUSR2(int sig) {
  printf("Señal SIGUSR2 recibida por %d\n", getpid());
  fflush(stdout);
}

/* manejador_SIGUSR2:*/
void manejador_SIGUSR1(int sig) {
  printf("Señal SIGUSR1 recibida por %d\n", getpid());
  fflush(stdout);
}

int main(void) {
    pid_t pid_gestor, pid;
    int i;

    /*Creamos los manejadores para SIGUSR1 y SIGUSR2*/
    struct sigaction act;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;


    /* Se arma la señal SIGUSR2. */
    act.sa_handler = manejador_SIGUSR2;
    if (sigaction(SIGUSR2, &act, NULL) < 0) {
        perror("SIGUSR2");
        exit(EXIT_FAILURE);
    }

    /* Se arma la señal SIGUSR1. */
    act.sa_handler = manejador_SIGUSR1;
    if (sigaction(SIGUSR1, &act, NULL) < 0) {
        perror("SIGUSR1");
        exit(EXIT_FAILURE);
    }

    pid_t pid_padre = getpid();
    pid_gestor = fork();

    if (pid_gestor < 0){
      perror ("fork");
      exit(EXIT_FAILURE);
    }

    if (pid_gestor == 0){
      printf ("PID DEL GESTOR: %d\n", getpid());
      for(i = 0; i < NUM_PROC; i++){             /*Gestor crea NUM_PROC hijos (participantes)*/
        pid = fork();

        if(pid <  0){
          perror ("fork");
          exit(EXIT_FAILURE);
        }

        else if(pid ==  0){
          kill(pid_gestor, SIGUSR2);              /*Avisa al gestor que esta preparado*/
          pause();
          printf("SOY EL HIJO CON PID: %d Y HE CAPTURADO LA SEÑAL\n", getpid());
          exit(EXIT_SUCCESS);
        }

        else if(pid >  0){
          pause();                              /*Espera por cada hijo a que le avise*/
        }
      }
      kill (pid_padre, SIGUSR2);  /*Kill del gestor a su padre*/
      pause();

      for (i=0; i<NUM_PROC; i++)
        wait(NULL);
      exit(EXIT_SUCCESS);
    }

    pause();
    kill (0, SIGUSR1);            /*Avisa a todo el grupo de que comienza la competición*/

    waitpid(pid_gestor, NULL, 0);
    exit(EXIT_SUCCESS);
}

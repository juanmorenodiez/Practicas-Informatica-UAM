/*
@fichero: ejercicio6a.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 11/03/2019
@descripción: ????
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/* manejador_SIGALRM:*/
void manejador_SIGALRM(int sig){
  printf("Alarma recibida\n");
  fflush(stdout);
}

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

#define N_ITER 5

int main (void) {
  pid_t pid;
  int counter;
  sigset_t set, oset;

  /*Creamos los manejadores para SIGUSR1 y SIGUSR2*/
  struct sigaction act;
  sigemptyset(&(act.sa_mask));
  act.sa_flags = 0;

  /* Se arma la señal SIGUSR2. */
  act.sa_handler = manejador_SIGUSR2;
  if (sigaction(SIGUSR2, &act, NULL) < 0) {
      perror("sigaction");
      exit(EXIT_FAILURE);
  }

  /* Se arma la señal SIGUSR1. */
  act.sa_handler = manejador_SIGUSR1;
  if (sigaction(SIGUSR1, &act, NULL) < 0) {
      perror("sigaction");
      exit(EXIT_FAILURE);
  }

  /* Se arma la señal SIGALRM. */
  act.sa_handler = manejador_SIGALRM;
  if (sigaction(SIGALRM, &act, NULL) < 0) {
      perror("sigaction");
      exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    printf ("PID hijo %d\n", getpid());
    alarm(40);
    /*Bloquear señales SIGUSR1, SIGUSR2, SIGALRM*/
    sigaddset (&set, SIGUSR1);
    sigaddset (&set, SIGUSR2);
    sigaddset (&set, SIGALRM);
    sigprocmask (SIG_BLOCK, &set, &oset);

    while(1) {
      for (counter = 0; counter < N_ITER; counter++) {
        printf("%d\n", counter);
        sleep(1);
      }
      /*Desbloquear señal SIGALRM, SIGUSR1*/
      sigdelset(&set, SIGUSR2);
      sigprocmask (SIG_UNBLOCK, &set, &oset);
      sleep(3);
    }
  }
  while (wait(NULL) > 0);
}

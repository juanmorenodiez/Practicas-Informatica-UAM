/*
@fichero: ejercicio6a.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 11/03/2019
@descripción: programa para comprobar el funcionamiento de las máscaras con manejadores
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/* manejador_SIGALRM:*/
void manejador_SIGTERM(int sig){
  printf("Soy %d y he recibido la señal SIGTERM\n", getpid());
  fflush(stdout);
}

#define N_ITER 5
int main (void) {
  pid_t pid;
  int counter;
  struct sigaction act;

  act.sa_handler = manejador_SIGTERM;
  sigemptyset(&(act.sa_mask));
  act.sa_flags = 0;

  if (sigaction(SIGTERM, &act, NULL) < 0) {
      perror("sigaction");
      exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    sigset_t set, oset;
    sigemptyset(&set);
    sigaddset(&set, SIGTERM);
    sigprocmask(SIG_BLOCK, &set, &oset);

    while(1) {
      for (counter = 0; counter < N_ITER; counter++) {
        printf("%d\n", counter);
        sleep(1);
      }
      sleep(3);
      sigsuspend(&oset);       /*El proceso se bloquea hasta que recibe SIGTERM del padre*/
      exit(EXIT_SUCCESS);
    }
  }

  sleep(10);

  if (kill(pid, SIGTERM) < 0){  /*Le envia a su hijo la señal SIGTERM*/
      perror("SIGTERM");
      exit(EXIT_FAILURE);
  }

  waitpid(pid, NULL, 0);
  exit(EXIT_SUCCESS);
}

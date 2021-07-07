/*
@fichero: ejercicio6a.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 11/03/2019
@descripción: programa para comprobar el funcionamiento de las mascaras,
junto con la señal de alarma.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define N_ITER 5
int main (void) {
  pid_t pid;
  int counter;
  sigset_t set, oset;

  pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    printf ("PID hijo %d\n", getpid());
    alarm(40);                          /*Establecemos alarma para dentro de 40 segundos*/
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

/*
@fichero: ejercicio8.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 11/03/2019
@descripción: programa para aprender el funcionamiento de los semaforos
de exclusion mutua y el acceso a las zonas criticas
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define N_READ 1
#define SECS 0
#define SEM1 "/lectura1"
#define SEM2 "/escritura1"

int lectores = 0;
int flag1 = 0;
int flag2 = 0;

/* manejador_SIGINT:*/
void manejador_SIGINT(int sig) {
  flag2 = 1;
  flag1 = 1;
  printf("Padre mandando señales a hijos %d\n", getpid());
  fflush(stdout);
  kill (0, SIGTERM);
}

void Leer(){
  printf("R-INI <%d>\n", getpid());
  fflush (stdout);
  sleep(1);
  printf("R-FIN <%d>\n", getpid());
  fflush (stdout);
}

void Escribir(){
  printf ("W-INI <%d>\n", getpid());
  fflush (stdout);
  sleep(1);
  printf("W-FIN <%d>\n", getpid());
  fflush (stdout);
}

void Lectura(sem_t *sem_lectura, sem_t *sem_escritura){
  sem_wait (sem_lectura);
  lectores++;
  if (lectores == 1)
    sem_wait (sem_escritura);
  sem_post (sem_lectura);

  Leer ();

  sem_wait (sem_lectura);
  lectores--;
  if (lectores == 0)
    sem_post (sem_escritura);
  sem_post (sem_lectura);
}

void Escritura(sem_t *sem_escritura) {
  sem_wait(sem_escritura);

  Escribir();

  sem_post(sem_escritura);
}

int main(void) {
    sem_t *sem_lectura = NULL, *sem_escritura = NULL;
    sigset_t set, oset;  /*Para bloquear a los hijos de la señal de interrupcion*/
    pid_t pid;
    int i;
    struct sigaction act;

    act.sa_handler = manejador_SIGINT;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;

    if (sigaction(SIGINT, &act, NULL) < 0) {
      perror("sigaction");
      exit(EXIT_FAILURE);
    }

    sem_unlink(SEM1);
    sem_unlink(SEM2);

    if ((sem_lectura = sem_open(SEM1, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
        perror("sem_open_lectura");
        exit(EXIT_FAILURE);
    }

    if ((sem_escritura = sem_open(SEM2, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
        perror("sem_open_escritura");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < N_READ; i++){
      pid = fork();

      if (pid < 0) {
          perror("fork");
          exit(EXIT_FAILURE);
      }

      else if(pid == 0){
        sigemptyset(&set);
        sigaddset(&set, SIGINT);

        if (sigprocmask(SIG_BLOCK, &set, &oset) < 0) {  /*Bloqueo señal sigint*/
          perror("sigprocmask");
          exit(EXIT_FAILURE);
        }

        while (flag1==0){
          Lectura(sem_lectura, sem_escritura);
          sleep(SECS);
        }
        sem_close(sem_lectura);
        sem_close(sem_escritura);
        exit(EXIT_SUCCESS);
      }
    }
    printf ("PID DEL PADRE %d\n", getpid());

    while (flag2==0) {
      Escritura(sem_escritura);
      sleep(SECS);
    }

    while (wait(NULL) < 0);
    sem_close(sem_lectura);
    sem_close(sem_escritura);
    exit(EXIT_SUCCESS);
}

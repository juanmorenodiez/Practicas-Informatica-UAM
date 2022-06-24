/*
@fichero: ejercicio9.c
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
#include <limits.h>

#define N_PROC 10
#define SEM1 "/escritor"
#define FICHERO "datos.txt"

void manejador_SIGTERM(int sig) {
    printf("Hijo ha recibido señal SIGTERM (PID %d)\n", getpid());
    fflush(stdout);
    exit(EXIT_SUCCESS);
}

int main(void) {
  FILE *f = NULL;                   /*datos.txt en el que van a escribir*/
  int k, w;

  sem_t *mutex1 = NULL;
  if ((mutex1 = sem_open(SEM1, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
      perror("sem_open_lectura");
      exit(EXIT_FAILURE);
  }

  sem_unlink(SEM1);
  int pid;
  for (int i = 0; i< N_PROC; i++){
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    else if(pid == 0){
      while (1){                      /*Se ejecuta hasta que el padre notifique ganador (SIGTERM)*/
        sem_wait(mutex1);
        f = fopen(FICHERO,"a");
        if (f==NULL)
          perror(FICHERO);

        fprintf(f, "%d\n", i);        /*El identificador será su variable i del bucle (diferente para cada proceso)*/
        fclose(f);
        sem_post(mutex1);
        usleep(((double) rand()/ RAND_MAX) * 100000);                     /*Tiempo aleatorio entre 0 y 1 decima*/
      }
      exit(EXIT_FAILURE);
    }
  }

  /*Si somos el padre, creamos una máscara para protegernos de SIGTERM*/
  sigset_t set, oset;
  sigemptyset(&set);
  sigaddset(&set, SIGTERM);
  sigprocmask(SIG_BLOCK, &set, &oset);

  int aux[N_PROC - 1];                /*Creamos array para ir almacenando todos los ids (y el numero de veces que han salido)*/

  int id;
  while (1){
    sleep(1);
    sem_wait(mutex1);
    f = fopen(FICHERO, "r");
    if (f==NULL)
      perror(FICHERO);

    for (k=0; k < N_PROC; k++){       /*Inicializamos array a 0*/
      aux[k] = 0;
    }

    while (!feof(f)){                 /*Leemos todo el datos.txt*/
      fscanf(f, "%d", &id);
      aux[id]++;
    }

    printf("Conteo de variables:\n");
    for (w=0; w<N_PROC; w++){
      printf("%d(%d)\t", w, aux[w]);        /*Imprimimos el conteno separado por un tabulador*/
    }
    printf ("\n");

    int ganador = -1;                 /*Variable usada en caso de varios ganadores*/
    for (w = 0; w < N_PROC; w++){
      if (aux[w] > 20){               /*Comprobamos si hay algun ganador*/
        if (ganador > -1){
          if (aux[ganador] < aux[w])
            ganador = w;
        }
        else
          ganador = w;
      }
    }

    if (ganador != -1){               /*Esto significa que alguien ha ganado*/
      printf("\nEl ganador de la carrera es el proceso con identificador %d\n", ganador);
      kill (0, SIGTERM);              /*Finalizan todos los hijos*/
      while (wait(NULL) > 0);
      sem_close(mutex1);
      fclose(f);
      remove (FICHERO);
      exit(EXIT_SUCCESS);
    }

    fclose(f);
    remove (FICHERO);
    sem_post(mutex1);
  }
}

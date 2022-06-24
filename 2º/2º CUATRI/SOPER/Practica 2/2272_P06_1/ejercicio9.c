#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define N_PROC 1
#define SECS 0
#define SEM1 "/escribir"
#define SEM2 "/escritura1"

int flag1 = 1
void manejador_SIGTERM(int sig) {
    printf("Hijo ha recibido señal (PID %d)\n", getpid());
    fflush(stdout);
    flag1 = -1;
}

int main(void) {
  FILE *f = NULL;                   /*Fichero en el que van a escribir*/
  double tiempo = 0;
  int k, w;
  f = fopen ("datos.txt", w);
  if (f==NULL){
    perror("Fichero");
  }

  sem_t *mutex1 = NULL
  if ((mutex1 = sem_open(SEM1, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
      perror("sem_open_lectura");
      exit(EXIT_FAILURE);
  }

  sem_t *mutex2 = NULL
  if ((mutex2 = sem_open(SEM1, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
      perror("sem_open_lectura");
      exit(EXIT_FAILURE);
  }

  sem_unlink(SEM1);

  for (int i = 0; i< N_PROC; i++){
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
      while (flag > 0){
        down(mutex1);
        down(mutex2);
        fopen(f,"a");
        fprintf(f, "%d\n", i);
        fclose(f);
        usleep(1);                     //Cambiar por un tiempo aleatorio
        tiempo += 0.0001;
        up(mutex2);
        up(mutex1);
      }
      exit(EXIT_SUCCESS);
    }
  }
  int aux[N_PROC - 1];
  for (k=0; k < N_PROC; k++){
    aux[k] = 0;
  }

  int ids;
  while (1){
    sleep(1);
    down(mutex2);
    fopen(f, "r");
    while (!FEOF(f)){
      fscanf("%d", id);
      aux[id]++;
    }

    fprintf("Conteo de variables:\n");
    for (w=0; w<N_PROC; w++){
      fprintf("/t%d", aux[w]);
    }

    for (w = 0; w < N_PROC; w++){
      if (aux[w] > 20){
        fprintf("El ganador de la carrera es el proceso con identificador %d\n", w);

        while (wait(NULL) > 0);

      }
    }
    fclose(f);
    up(mutex2);
  }





}

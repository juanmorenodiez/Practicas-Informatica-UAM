/*
@fichero: ejercicio2.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 05/03/2019
@descripción: programa que prueba el envío de
señales mediante el uso de procesos.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include "queue.h"
#define SHM_NAME "/SharedQueue"
#define SEM1 "/structure"
#define SEM2 "/structure2"

int main(int argc , char *argv[]){

	sem_t *sem_fillCount = NULL;
	sem_t *sem_emptyCount = NULL;

	if ((sem_fillCount = sem_open(SEM1, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED) {
    perror("sem_open_lectura");
    exit(EXIT_FAILURE);
  }

  if ((sem_emptyCount = sem_open(SEM2, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, SIZE)) == SEM_FAILED) {
    perror("sem_open_escritura");
    exit(EXIT_FAILURE);
  }


	sem_unlink(SEM1);
	sem_unlink(SEM2);

	int fd = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); /* Create a memory segment for reading and writing. If it does not exist, create it*/
	if(fd == -1){
		fprintf (stderr, "Error opening the shared memory segment \n");
		exit(EXIT_FAILURE);
	}

	int error = ftruncate(fd, sizeof(Queue));
	if(error == -1){
		fprintf (stderr, "Error resizing the shared memory segment \n");
		shm_unlink(SHM_NAME);
		exit(EXIT_FAILURE);
	}

	Queue *Circular_queue = mmap(NULL, sizeof(Queue), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(Cilcular_queue == MAP_FAILED){
		fprintf (stderr, "Error mapping the shared memory segment \n");
		shm_unlink(SHM_NAME);
		exit(EXIT_FAILURE);
	}

	Circular_queue = queue_create();

	printf ("Introduce cadena de caracteres: \n");
	while (!EOF(stdout)){
		char c = getchar();
		sem_wait(emptyCount);
		if (queue_insert(Circular_queue, c) == ERROR){
			printf("No se ha podido insertar en la cola el caracter %c\n", c);
		}
		sem_post(fillCount);
	}

	queue_insert(Circular_queue, "/0");						/*Imprimimos el último caracter*/

	munmap(Circular_queue, sizeof(*Circular_queue));
	shm_unlink(SHM_NAME);
	exit(EXIT_SUCCESS);
}

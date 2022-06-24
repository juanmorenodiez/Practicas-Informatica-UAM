/*
@fichero: ejercicio2.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grsem_posto: 2272
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
#define SHM_NAME "/SharedMem"
#define SEM1 "/structure"
#define SEM2 "/structure2"


int main(int argc , char *argv[]){
	sem_t *caracteres = NULL;
	sem_t *restantes = NULL;
	int item = 0;

	int fd_shm = shm_open(SHM_NAME, O_RDONLY, 0); /*Open memory for reading*/
	if(fd_shm == -1){
		fprintf (stderr, "Error opening the shared memory segment \n");
		return EXIT_FAILURE;
	}

	/* Map the memory segment */
	Circular_queue *Queue = mmap(NULL, sizeof(Queue), PROT_READ, MAP_SHARED, fd_shm, 0);
	if(example_struct == MAP_FAILED){
		fprintf (stderr, "Error mapping the shared memory segment \n");
		return EXIT_FAILURE;
	}

	if ((caracteres = sem_open(SEM1, 0_EXCL)) == SEM_FAILED) {
		perror("sem_open_caracteres");
		shm_unlink(SHM_NAME);
		munmap(Queue, sizeof(Circular_queue));
		exit(EXIT_FAILURE);
	}

	if ((restantes = sem_open(SEM2, 0_EXCL)) == SEM_FAILED) {
		perror("sem_open_restantes");
		shm_unlink(SHM_NAME);
		munmap(Queue, sizeof(Circular_queue));
		sem_unlink(SEM1);
		sem_close(caracteres);
		exit(EXIT_FAILURE);
	}

	item = queue_extract(Queue);

	while (item != \0) { //* no se si se pone "\0" o '\0' o sin nada XDDDD*/
		sem_wait(caracteres);
		sem_post(restantes);
		printf("%d", item);
	}

	queue_print(Queue);		/*Print the queue*/
	/* Unmap the shared memory */
	munmap(example_struct, sizeof(*example_struct));
	return EXIT_SUCCESS;

}

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
#define WORD 32

typedef struct{
	int previous_id; 			//!< Id of the previous client.
	int id; 							//!< Id of the current client.
	char name[NAME_MAX]; 	//!< Name of the client.
} ClientInfo;

int main(int argc , char *argv[]){
	pid_t pid;
	int i;

	if (argc != 2){
		fprintf(stderr, "Numero de parámetros incorrecto\nIntroduce un número como parámetro (número de hijos)\n");
		exit(EXIT_FAILURE);
	}

	int fd = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); /* Create a memory segment for reading and writing. If it does not exist, create it*/
	if(fd == -1){
		fprintf (stderr, "Error opening the shared memory segment \n");
		exit(EXIT_FAILURE);
	}

	int error = ftruncate(fd, sizeof(ClientInfo));
	if(error == -1){
		fprintf (stderr, "Error resizing the shared memory segment \n");
		shm_unlink(SHM_NAME);
		exit(EXIT_FAILURE);
	}

	ClientInfo *client_struct = mmap(NULL, sizeof(ClientInfo), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(client_struct == MAP_FAILED){
		fprintf (stderr, "Error mapping the shared memory segment \n");
		shm_unlink(SHM_NAME);
		exit(EXIT_FAILURE);
	}

	client_struct->previous_id = -1;
	client_struct->id = 0;
	int n = atoi(argv[1]);
	if (n <= 0){
		fprintf(stderr, "El argumento tiene que ser mayor que 0\n");
		exit(EXIT_FAILURE);
	}

	/*Creamos semáforos de exclusión mutua*/
	sem_t *mutex1 = NULL;
	if ((mutex1 = sem_open(SEM1, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
			perror("sem_open_lectura");
			exit(EXIT_FAILURE);
	}
	sem_unlink(SEM1);

	sem_t *mutex2 = NULL;
	if ((mutex2 = sem_open(SEM2, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
			perror("sem_open_lectura");
			exit(EXIT_FAILURE);
	}
	sem_unlink(SEM2);


	for(i = 0; i < n; i++){
		pid = fork();

		if(pid <  0){
			printf("Error al emplear fork\n");
			exit(EXIT_FAILURE);
		}

		else if(pid ==  0){
			char *nombre = (char *)malloc(WORD * sizeof(char));

			if (nombre == NULL){
					perror("reserva cadena caracteres");
					exit (EXIT_FAILURE);
			}

			sleep((double) rand()  * 10.0 / (double)RAND_MAX);
			sem_wait(mutex1);
			sem_wait(mutex2);
			client_struct->previous_id ++;
			printf ("Introduce el nombre del nuevo cliente: \n");
			scanf("%s", nombre);												/*Leemos nombre de terminal*/
			strcpy(client_struct->name, nombre);				/*Lo escribimos en memoria compartida*/
			kill(getppid(), SIGUSR1);										/*Mandamos señal al padre*/
			sem_post (mutex2);
			sem_post (mutex1);
			free (nombre);
			exit(EXIT_SUCCESS);
		}
	}

	/*Suspendemos al padre para que vaya leyendo cada señal de SIGUSR1 recibid*/
	sigset_t set, oset;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	/*sigprocmask(SIG_BLOCK, &set, &oset);
	*/
	for (i = 0; i < n; i++){
		pause();
		sem_wait (mutex2);
		printf("test\n");
		fprintf(stdout, "Id previo: %d\t Id actual: %d \t Nombre de usuario: %s\n", client_struct->previous_id, client_struct->id, client_struct->name);
		sem_post (mutex2);
	}


	/*Esperamos por cada hijo que se ha creado*/
	for(i = 0; i < n; i++)
		if (wait(NULL)==-1)
			printf ("Error al esperar al hijo");

	sem_close(mutex1);
	sem_close(mutex2);
	munmap(client_struct, sizeof(*client_struct));
	shm_unlink(SHM_NAME);
	exit(EXIT_SUCCESS);
}

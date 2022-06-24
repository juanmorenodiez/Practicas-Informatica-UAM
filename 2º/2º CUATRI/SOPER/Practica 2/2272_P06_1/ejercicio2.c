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
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_PROC 4

int main(void){
	pid_t pid;
	int i;

	for(i = 0; i < NUM_PROC; i++){
		pid = fork();

		if(pid <  0){
			printf("Error al emplear fork\n");
			exit(EXIT_FAILURE);
		}

		else if(pid ==  0){
			printf("Soy el proceso hijo <%d>\n", getpid());
			sleep(30);
			printf("Soy el proceso hijo <%d> y ya me toca terminar\n", getpid());
			exit(EXIT_SUCCESS);
		}

		else if(pid >  0){
			sleep(5);
			if (kill (pid, 15) == 1){
				printf("Error mandando señal\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	/*Esperamos por cada hijo que se ha creado*/
	for(i = 0; i < NUM_PROC; i++)
		if (wait(NULL)==-1)
			printf ("Error al esperar al hijo");

	exit(EXIT_SUCCESS);
}

/*
@fichero: p1_exercise_3.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 05/02/2019
@descripción: código que prueba el funcionamiento de
la función fork y el uso de las funciones que devuelven
los pids y los ppids.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PROC 3

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
			printf("PID HIJO: %d\tPID PADRE: %d\n", getpid(), getppid());
			exit(EXIT_SUCCESS);
		}
		else if(pid >  0)
			printf("PADRE %d\n", i);
	}

	/*Esperamos por un hijo*/
	wait(NULL);

	exit(EXIT_SUCCESS);
}

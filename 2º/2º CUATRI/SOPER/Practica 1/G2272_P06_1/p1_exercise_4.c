/*
@fichero: p1_exercise_4.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 05/02/2019
@descripción: código que genera el árbol de procesos
correspondiente al ejercicio 4.
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

		else if(pid ==  0)
			exit(EXIT_SUCCESS);
		}

	/*Esperamos por cada hijo que se ha creado*/
	for(i = 0; i < NUM_PROC; i++)
		if (wait(NULL)==-1)
			printf ("Error al esperar al hijo");

	exit(EXIT_SUCCESS);
}

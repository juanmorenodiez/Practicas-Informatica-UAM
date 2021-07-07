/* * File:   p3_testqueue.c* Author: Profesores de PROG2*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "queue.h"
#include "nodo.h"
#define MAX 255

extern int errno;

void mainCleanUp (Queue *q1, Queue *q2, Queue*q3, Node *pn, FILE *pf) {
	if (pn) node_destroy(pn);
	if (q1) queue_destroy (q1);
	if (q2) queue_destroy (q2);
	if (q3) queue_destroy (q3);
	if (pf) fclose (pf);    
}

int main(int argc, char** argv){
	FILE *pf=NULL;
	Queue *q1=NULL, *q2=NULL, *q3=NULL;
	Node *pn=NULL;
	int id, i, npoints, middle;
	char name[MAX];
	char s[MAX];

	if (argc < 2){
	fprintf(stderr, "Error:Introduzca como argumento nombre del fichero con los nodos.\n");
	return EXIT_FAILURE;
	}

	pf = fopen(argv[1], "r");

	if (pf==NULL){
		fprintf (stderr, "Error apertura fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if (fgets(s, MAX, pf)==NULL) {
		fprintf(stderr, "Error lectura de fichero: %s\n", strerror(errno));
		mainCleanUp (q1, q2, q3, pn, pf);
		return EXIT_FAILURE;
	}

	if (sscanf(s, "%d\n", &npoints) !=1 ){fprintf(stderr, "Error formato datos en fichero: %s\n", strerror(errno));
		mainCleanUp (q1, q2, q3, pn, pf);
		return EXIT_FAILURE;
	}    

	pn = node_ini();
	if (pn==NULL) {
		fprintf(stderr, "Error: inicializacion de nodo.\n");
		mainCleanUp (q1, q2, q3, pn, pf);
		return EXIT_FAILURE;
	}

	q1 = queue_ini((destroy_element_function_type)node_destroy, (copy_element_function_type)node_copy, (print_element_function_type)node_print);
	q2 = queue_ini((destroy_element_function_type)node_destroy, (copy_element_function_type)node_copy, (print_element_function_type)node_print);
	q3 = queue_ini((destroy_element_function_type)node_destroy, (copy_element_function_type)node_copy, (print_element_function_type)node_print);

	if (!q1 || !q2 || !q3) {
		fprintf(stderr, "Error: inicializacion de cola.\n");mainCleanUp (q1, q2, q3, pn, pf);
		return EXIT_FAILURE;
	}

	printf("Inicialmente:\n");
	printf("Cola 1: \n");
	queue_print(stdout, q1);
	printf("Cola 2: \n");
	queue_print(stdout, q2);
	printf("Cola 3: \n");
	queue_print(stdout, q3);
	printf("\nAñadiendo %d elementos a q1:\n", npoints);

	for (i=0; i<npoints; i++){
		if (fgets(s, MAX, pf) == NULL){
			fprintf(stderr, "Error lectura de fichero: %s\n", strerror(errno));
			mainCleanUp (q1, q2, q3, pn, pf);
			return EXIT_FAILURE;
		}

		if(sscanf(s, "%d %s \n", &id, name) !=2 ){
			fprintf(stderr, "Error formato datos en fichero: %s\n", strerror(errno));
			mainCleanUp (q1, q2, q3, pn, pf);
			return EXIT_FAILURE;
		}

		node_setId(pn, id);

		node_setName(pn, name);

		if (queue_insert(q1, pn) == ERROR) {
			fprintf(stderr,"Error: inserción en cola.\n");
			mainCleanUp (q1, q2, q3, pn, pf);
			return EXIT_FAILURE;
		}

		printf("Cola 1: \n");
		queue_print(stdout, q1);
		printf("\nCola 2: ");
		queue_print(stdout, q2);
		printf("\nCola 3: ");
		queue_print(stdout, q3);
		printf("\n");
		printf("\n");
	}
	
	node_destroy(pn); 
	
	pn = NULL;

	printf("\n<<<Pasando la primera mitad de Cola 1 a Cola 2\n");
	
	npoints = queue_size(q1);
	
	middle = npoints/2;
	
	for(i=0; i< middle; i++){
		pn = queue_extract(q1);
		if (queue_insert(q2, pn)== ERROR) {
			fprintf(stderr, "Error: inserción en cola 2.\n");
			mainCleanUp (q1, q2, q3, pn, pf);
			return EXIT_FAILURE;
		}

		node_destroy(pn); 
		
		pn = NULL;printf("Cola 1: \n");
		
		queue_print(stdout, q1);
		
		printf("\nCola 2: ");
		
		queue_print(stdout, q2);
		
		printf("\nCola 3: ");
		
		queue_print(stdout, q3);
		
		printf("\n");
		
	}
	printf("\n<<<Pasando la segunda mitad de Cola 1 a Cola 3\n");
	
	for(i=npoints/2; i< npoints; i++){
		
		pn = queue_extract(q1);
		if (queue_insert(q3, pn) == ERROR) {
			fprintf(stderr,"Error: inserción en cola 3.\n");
			mainCleanUp (q1, q2, q3, pn, pf);
			return EXIT_FAILURE;
		}

		node_destroy(pn); 
		
		pn = NULL;
		
		printf("Cola 1: \n");
		
		queue_print(stdout, q1);
		
		printf("\nCola 2: ");
		
		queue_print(stdout, q2);
		
		printf("\nCola 3: ");
		
		queue_print(stdout, q3);
		
		printf("\n");
	
	}

	mainCleanUp (q1, q2, q3, pn, pf);

	return EXIT_SUCCESS;
}
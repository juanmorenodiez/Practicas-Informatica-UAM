#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

int main(int argc, char *argv[]){
	FILE* f = NULL;
	Graph* graph;
	

	if(argc < 2){
		fprintf(stdout, "ERROR: La sintaxis correcta es ==> (ejecutable) (nombre del archivo)\n");
		return 1;
	}

	graph = graph_ini();

	if(!graph){
		return 1;
	}

	f = fopen(argv[1], "r");

	if(!f){
		graph_destroy(graph);
		fprintf(stdout, "ERROR: No se encuentra el archivo.\n");
		return 1;
	}

	graph_readFromFile(f, graph);

	graph_print(stdout, graph);

	fclose(f);
	
	graph_destroy(graph);

	return 0;
}
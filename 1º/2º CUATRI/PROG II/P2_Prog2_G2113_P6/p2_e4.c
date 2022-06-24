#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "nodo.h"

void print_result(Node* nodo1, Node* nodo2, Graph* graph);

int main(int argc, char *argv[]){
	FILE* f = NULL;
	Graph* graph = NULL;
	Node* nodo1 = NULL;
	Node* nodo2 = NULL;
	int from_id, to_id;

	if(argc != 4){
		if(argc == 1){
			fprintf(stdout, "ERROR: La sintaxis correcta es ==> %s < Nombre del archivo > < Entero > < Entero >\n", argv[0]);
		}else if(argc == 2){
			fprintf(stdout, "ERROR: La sintaxis correcta es ==> %s %s < Entero > < Entero >\n", argv[0], argv[1]);			
		}
		return 1;
	}

	from_id = atoi(argv[2]);

	to_id = atoi(argv[3]);

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

	nodo1 = graph_getNode(graph, atoi(argv[2]));

	if(!nodo1){
		graph_destroy(graph);
		return 1;
	}

	nodo2 = graph_findDeepSearch(graph, from_id, to_id);

	print_result(nodo1, nodo2, graph);

	graph_destroy(graph);

	node_destroy(nodo1);

	node_destroy(nodo2);

	fclose(f);
	
	return 0;
}

void print_result(Node* nodo1, Node* nodo2, Graph* graph){

	graph_print(stdout, graph);

	if(nodo2){
		fprintf(stdout, "\nSe puede encontrar un camino entre:\n");
		node_print(stdout, nodo1);
		fprintf(stdout, " ----> ");
		node_print(stdout, nodo2);
		fprintf(stdout, "\n");
	}else{
		fprintf(stdout, "No es posible encontrar un camino.\n");
	} 

	return;
}
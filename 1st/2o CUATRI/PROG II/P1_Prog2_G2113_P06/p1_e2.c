#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

int main(int argc, char *argv[]){
	Node *n1;
	Node *n2;
	Graph *graph;

	n1 = node_ini();

	n1 = node_setId(n1, 111);
	n1 = node_setName(n1, "first");

	n2 = node_ini();

	n2 = node_setId(n2, 222);
	n2 = node_setName(n2, "second");
	graph = graph_ini();

	fprintf(stdout, "Insertando nodo 1... Resultado...:%d\n", graph_insertNode(graph, n1));
	fprintf(stdout, "Insertando nodo 2... Resultado...:%d\n", graph_insertNode(graph, n2));

	fprintf(stdout, "Insertando edge: nodo2 --> nodo1\n");
	graph_insertEdge(graph, node_getId(n2), node_getId(n1));

	fprintf(stdout, "¿Conectados nodo1 y nodo2?");

	if(graph_areConnected(graph, node_getId(n1), node_getId(n2)) == TRUE)
		fprintf(stdout, "Sí\n");
	else 
		fprintf(stdout, "No\n");

	fprintf(stdout, "¿Conectados nodo2 y nodo1?");
	
	if(graph_areConnected(graph, node_getId(n2), node_getId(n1)) == TRUE)
		fprintf(stdout, "Sí\n");
	else 
		fprintf(stdout, "No\n");

	fprintf(stdout, "Insertando nodo 2... Resultado...:%d\n", graph_insertNode(graph, n2));

	graph_print(stdout, graph);

	node_destroy(n1);
	node_destroy(n2);
	graph_destroy(graph);

	return 0;
}
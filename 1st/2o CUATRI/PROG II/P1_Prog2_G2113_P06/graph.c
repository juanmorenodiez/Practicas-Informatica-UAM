#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "graph.h"
#include "nodo.h"
#include "types.h"

#define MAX_NODE 4096
#define MAX_LINE 256

struct _Graph{
	Node* node[MAX_NODE];
	int num_nodes;
	Bool connections[MAX_NODE][MAX_NODE];
};

int find_node_index(const Graph * g, int nId1);
int* graph_getConectionsIndex(const Graph * g, int index);


int find_node_index(const Graph * g, int nId1) {
	int i;

	if (!g) return -1;

	for(i=0; i < g->num_nodes; i++){
		if (node_getId (g->node[i]) == nId1) return i;
	}
	/* ID not find*/
	return -1;

	
}

int* graph_getConectionsIndex(const Graph * g, int index) {
	int *array = NULL,i, j=0, size;

	if (!g) return NULL;

	if (index < 0 || index >g->num_nodes) return NULL;

	/* get memory for the array with the connected nodes index*/
	size = node_getConnect (g->node[index]);

	array = (int *) malloc(sizeof(int) * size);

	if (!array) {
		/* print errorr message*/
		fprintf (stderr, "%s\n", strerror(errno));
		return NULL;
	}

/* asigno valores al array con los indices de los nodos conectados*/
	for(i = 0; i< g->num_nodes; i++) {
		if (g->connections[index][i] == TRUE) {
			array[j] = i;
			j++;
		}
	}

	return array;
}

Graph* graph_ini(){
	int i, j;

	Graph *newGraph;

	newGraph = (Graph*) malloc (sizeof(Graph));

	if(!newGraph)
		return NULL;
	for(i=0 ; i<MAX_NODE ; i++){
		newGraph->node[i] = NULL;
	}

	newGraph->num_nodes = 0;

	for(i=0 ; i<MAX_NODE ; i++){
		for(j=0; j<MAX_NODE ; j++){
			newGraph->connections[i][j] = FALSE;
		}
	}

	return newGraph;
}

Status graph_destroy(Graph *g){
	int i;

	if(!g){
		return ERROR;
	}

	for(i=0; i<MAX_NODE ; i++){
		node_destroy(g->node[i]);
	}


	free(g);

	return OK;

}

Status graph_insertNode(Graph * g, const Node* n){
  int i, flag=0, id;
  Node *aux;

  id = node_getId(n);

  for(i=0; i < MAX_NODE; i++){
    if (id == node_getId(g->node[i])) {
      flag = 1;
    }
  }

  if(flag == 1) {
    return ERROR;
  }

  aux = node_copy(n);

  if (aux == NULL) {
    return ERROR;
  }

  g->node[g->num_nodes] = aux;
  g->num_nodes++;

  return OK;
}

Status graph_insertEdge(Graph * g, const int nId1, const int nId2){
  int i, j;
  int pos1 = 0, pos2 = 0;

  if (g == NULL) {
    return ERROR;
  }

  for(i=0; i < MAX_NODE; i++){
    if (nId1 == node_getId(g->node[i])) {
      pos1 = i;
      node_setConnect(g->node[i], node_getConnect(g->node[i])+1);
    }
  }

  for(j=0; j < MAX_NODE; j++){
    if (nId2 == node_getId(g->node[j])) {
      pos2 = j;
      node_setConnect(g->node[j], node_getConnect(g->node[j])+1);
    }
  }

  g->connections[pos1][pos2] = TRUE;

  return OK;
}

Node *graph_getNode (const Graph *g, int nId){
	int i = 0, id;
	if(!g)
		return NULL;

	for(i=0; i < g->num_nodes ; i++){

		id = node_getId(g->node[i]);

		if (id == nId){
			return g->node[i];
		}
	}

	return NULL;
}

Status graph_setNode (Graph *g, const Node *n){
	int id, i=0;
	if(!g){
		return ERROR;
	}

	id = node_getId(n);

	for(i=0 ; i<g->num_nodes ; i++){

		if(node_getId(g->node[i]) == id) {

			node_setName(g->node[i], node_getName(n));
			node_setConnect(g->node[i], node_getConnect(n));

			return OK;
		}

	}

	return ERROR;
}

int * graph_getNodesId (const Graph * g){
	int *tabla;
	int i;

	tabla = (int*) calloc (g->num_nodes, sizeof(int));

	if(tabla == NULL){
		return NULL;
	}

	for(i=0 ; i < g->num_nodes ; i++){
		tabla[i] = node_getId(g->node[i]);
		return tabla;
	}

	return NULL;
}

int graph_getNumberOfNodes(const Graph * g){
	if(!g){
		return -1;
	}

	return g->num_nodes;
}

int graph_getNumberOfEdges(const Graph * g){
	int i=0, j=0, contador=0;

	if(!g){
		return -1;
	}
	for(i=0; i<MAX_NODE ; i++){
		for(j=0; j<MAX_NODE ; j++){
			if(g->connections[i][j] == TRUE){
				contador++;
			}
		}
	}

	return contador;
}

Bool graph_areConnected(const Graph * g, const int nId1, const int nId2){
	int id1,id2, i;

	for(i=0 ; i<MAX_NODE ; i++){
		if(node_getId(g->node[i]) == nId1){
			id1 = i;
		}
	}

	for(i=0 ; i<MAX_NODE ; i++){
		if(node_getId(g->node[i]) == nId2){
			id2 = i;
		}
	}

	if(g->connections[id1][id2] == TRUE){
		return TRUE;
	}
	else {
		return FALSE;
	}

}

int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId){
	int i=0;

	if(!g){
		return -1;
	}

	for(i=0 ; i < g->num_nodes ; i++){

		if(node_getId(g->node[i]) == fromId) {

			return node_getConnect(g->node[i]);

		}
	}

	return	-1;
}

int* graph_getConnectionsFrom(const Graph * g, const int fromId){
	int *fila;
	int i=0, j=0;

	fila = (int*) calloc (g->num_nodes, sizeof(int));

	for(i=0 ; i < MAX_NODE ; i++){

		if(node_getId(g->node[i]) == fromId){

			for(j=0 ; j < MAX_NODE ; j++){

				if(g->connections[i][j] == TRUE){

					fila[j] = node_getId(g->node[j]); 

				}

			}

			return fila;

		}

	}

	return NULL;

}

int graph_print(FILE *pf, const Graph * g){
	int i=0, j=0;
	int errno;

	if(!pf || !g){
		fprintf(stderr, "Error: %d\n", errno);
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return -1;
	}

	fprintf(stdout, "Num of nodes ==> %d\n", g->num_nodes);

	for(i=0 ; i<g->num_nodes ; i++){
		node_print(pf, g->node[i]);
			for(j=0; j<MAX_NODE ; j++){
				if(g->connections[i][j] == TRUE){
					fprintf(stdout, " %d" , node_getId(g->node[j]));
				}
			}
		fprintf(stdout, "\n");
	}	
	return 0;
}

Status graph_readFromFile (FILE *fin, Graph *g) {
Node *n;
char buff[MAX_LINE], name[MAX_LINE];
int i, nnodes = 0, id1, id2;
Status flag = ERROR;
int NO_FILE_POS_VALUES = 2;

/* read number of nodes */
if ( fgets (buff, MAX_LINE, fin) != NULL)
	if ( sscanf(buff, "%d", &nnodes) != 1) 
		return ERROR;

/* init buffer_node */
n = node_ini();

if (!n) 
	return ERROR;

/* read nodes line by line */
for(i=0; i < nnodes; i++) {
	if ( fgets(buff, MAX_LINE, fin) != NULL)
		if (sscanf(buff, "%d %s", &id1, name) != NO_FILE_POS_VALUES) 
			break;

/* set node name and node id */
	node_setName (n, name);
	node_setId (n, id1);

/* insert node in the graph */
	if ( graph_insertNode (g, n) == ERROR) break;
}

/* Check if all node have been inserted */
if (i < nnodes) {
	node_destroy(n);
	return ERROR;
}

/* read connections line by line and insert it */
while ( fgets(buff, MAX_LINE, fin) ){
	if ( sscanf(buff, "%d %d", &id1, &id2) == NO_FILE_POS_VALUES )
		if (graph_insertEdge(g, id1, id2) == ERROR) 
			break;
}

/* check end of file */
if (feof(fin)) flag = OK;
/* clean up, free resources */
	node_destroy (n);
	return flag;
}
/** 
 * @brief Define el TAD de graph
 * 
 * @file graph.c
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0 
 * @date 12-03-2019
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "graph.h"
#include "nodo.h"
#include "types.h"
#include "queue.h"

#define MAX_NODE 4096
#define MAX_LINE 256

struct _Graph{
	Node* node[MAX_NODE];
	int num_nodes;
	Bool connections[MAX_NODE][MAX_NODE];
	int num_Edges;
};

int find_node_index(const Graph * g, int nId1);
int* graph_getConectionsIndex(const Graph * g, int index);

/**
* @brief Encuentra donde se encuentra el nodo. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @param int nId1
* @return int i
*/
int find_node_index(const Graph * g, int nId1) {
	int i;

	if (!g) return -1;

	for(i=0; i < g->num_nodes; i++){
		if (node_getId (g->node[i]) == nId1) return i;
	}
	/* ID not find*/
	return -1;

	
}

/**
* @brief Encuentra las conexiones del nodo con indice index. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @param int index
* @return int* array
*/
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

/**
* @brief Crea e inicializa el grafo. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param 
* @return Graph* newGraph
*/
Graph* graph_ini(){
	int i, j;

	Graph *newGraph;

	newGraph = (Graph*) malloc (sizeof(Graph));

	if(!newGraph)
		return NULL;
	
	newGraph->num_nodes = 0;

	newGraph->num_Edges = 0;

	for(i=0 ; i<MAX_NODE ; i++){
		newGraph->node[i] = NULL;

		for(j=0; j<MAX_NODE ; j++){
			newGraph->connections[i][j] = FALSE;
		}
	}

	return newGraph;
}

/**
* @brief Destruye el nodo
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @return OK si todo correcto
*         ERROR si hay algun error
*/
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

/**
* @brief Inerta en el grafo el nodo correspondiente.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @param Node* n
* @return OK si todo correcto
*         ERROR si hay algun error
*/
Status graph_insertNode(Graph * g, const Node* n){
  Node *aux;

  if(g->num_nodes == MAX_NODE){
  	return ERROR;
  }

  if(find_node_index(g, node_getId(n)) != -1){
  	return ERROR;
  }

  aux = node_copy(n);

  if (aux == NULL) {
    return ERROR;
  }

  node_setConnect(aux, 0);
  g->node[g->num_nodes] = aux;
  g->num_nodes++;

  return OK;
}

/**
* @brief Inserta en el grafo las uniones entre ids.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @param int nId1
* @param int nId2
* @return OK si todo correcto
*         ERROR si hay algun error
*/
Status graph_insertEdge(Graph * g, const int nId1, const int nId2){
  int pos1 = 0, pos2 = 0;

  if (g == NULL) {
    return ERROR;
  }

  pos1 = find_node_index(g, nId1);

  if(pos1 == -1){
  	return ERROR;
  }

  pos2 = find_node_index(g, nId2);

  if(pos2 == -1){
  	return pos2;
  }

  g->connections[pos1][pos2] = TRUE;

  g->num_Edges++;

  return OK;
}

/**
* @brief Coge el nodo de id nId.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @param int nId
* @return Node*
*/
Node *graph_getNode (const Graph *g, int nId){
	int i = 0, id;
	Node* aux = NULL;
	if(!g)
		return NULL;

	for(i=0; i < g->num_nodes ; i++){

		id = node_getId(g->node[i]);

		if (id == nId){
			aux = node_copy(g->node[i]);
			return aux;
		}
	}

	return NULL;
}

/**
* @brief Setea el nodo en el grafo.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @param Node* n
* @return OK si todo correcto
*         ERROR si hay algun error
*/
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
			node_setEtq(g->node[i], node_getEtq(n));
			node_setAntecesor(g->node[i], node_getAntecesor(n));

			return OK;
		}

	}

	return ERROR;
}

/**
* @brief Coge los id de los nodos del grafo.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @return int* tabla
*/
int * graph_getNodesId (const Graph * g){
	int *tabla;
	int i;

	tabla = (int*) calloc (g->num_nodes, sizeof(int));

	if(tabla == NULL){
		return NULL;
	}

	for(i=0 ; i < g->num_nodes ; i++){
		tabla[i] = node_getId(g->node[i]);
	}

	return tabla;
}

/**
* @brief Coge el numero de nodos del grafo.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @return int g->num_nodes
*/
int graph_getNumberOfNodes(const Graph * g){
	if(!g){
		return -1;
	}

	return g->num_nodes;
}

/**
* @brief Coge los numeros de edges contenidos en el grafo.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @return int tabla
*/
int graph_getNumberOfEdges(const Graph * g){
	if(!g){
		return -1;
	}

	return g->num_Edges;
}

/**
* @brief Compara si los nodos están conectados o no.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @param int nId1
* @param int n1d2
* @return TRUE si están conectados
*         FALSE si no lo están
*/
Bool graph_areConnected(const Graph * g, const int nId1, const int nId2){
	int id1,id2;

	id1 = find_node_index(g, nId1);

	if(id1 == -1){
		return FALSE;
	}

	id2 = find_node_index(g, nId2);

	if(id2 == -1){
		return FALSE;
	}

	return g->connections[id1][id2];
}

/**
* @brief Coge el numero de conexiones del nodo de id fromId.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @param int fromId
* @return int 
*/
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
	int i=0, k=0, j=0;

	i = find_node_index(g, fromId);

	if(i == -1){
		return NULL;
	}

	fila = (int*) calloc (g->num_nodes, sizeof(int));

	for(i=0 ; i < g->num_nodes ; i++){

		if(node_getId(g->node[i]) == fromId){

			for(j=0 ; j < g->num_nodes ; j++){

				if(g->connections[i][j] == TRUE){

					fila[k] = node_getId(g->node[j]); 
					k++;

				}

			}

			return fila;

		}

	}

	return NULL;

}

/**
* @brief Imprime el grafo.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param FILE* pf 
* @param Graph* g
* @return int bytes
*/
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

/**
* @brief Lee del fichero los diferentes datos del nodo.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param FILE* fin
* @param Graph* g
* @return OK si todo es correcto
*         ERROR si hay algún error
*/
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

/**
* @brief Comprueba si existe camino entre nodos.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Graph* g
* @param int from_id
* @param int to_id
* @return Node* si existe camino.
*         NULL si no existe camino.
*/
Node* graph_findDeepSearch (Graph *g, int from_id, int to_id){
	Node* node1 = NULL;
	Node* u = NULL;
	Node* w = NULL;
	Queue* queue = NULL;
	Bool encontrado = FALSE;
	int uId, IdAux;
	int i = 0;
	int* fila = NULL;

	if(!g){
		return NULL;
	}

	node1 = graph_getNode(g, from_id);

	if(node1 == NULL){
		return NULL;
	}

	queue = queue_ini((destroy_element_function_type)node_destroy, (copy_element_function_type)node_copy, (print_element_function_type)node_print);

	if(!queue){
		return NULL;
	}

	if(queue_insert(queue, node1) == ERROR){
		return NULL;
	}

	node_destroy(node1);

	while(queue_isEmpty(queue) == FALSE && encontrado == FALSE){
		u = queue_extract(queue);
		
		uId = node_getId(u);

		IdAux = find_node_index(g, uId);
		if(node_getEtq(g->node[IdAux]) == BLANCO){

			node_setEtq(g->node[IdAux], NEGRO);

			fila = graph_getConnectionsFrom(g, uId);

			for(i=0 ; i < g->num_nodes ; i++){
				w = graph_getNode(g, fila[i]);
				if(fila[i] == to_id){
					encontrado = TRUE;
					break;
				}else{
					queue_insert(queue, w);
					node_destroy(w);
				}
			}
			break;
		}
	}

	free(fila);

	node_destroy(u);

	queue_destroy(queue);

	if(encontrado == TRUE){
		return w;
	}else{
		return NULL;
	}
}
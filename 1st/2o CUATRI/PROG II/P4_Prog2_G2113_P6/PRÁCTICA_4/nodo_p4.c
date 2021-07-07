/** 
 * @brief Define el TAD de nodos
 * 
 * @file nodo.c
 * @author Camilo Jené Conde y Juan Moreno Diez 
 * @version 1.0 
 * @date 12-03-2019
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo.h"
#include "types.h"

#define TAM 100


struct _Node{
	char* name;
	int id;
};

/**
* @brief Crea e inicializa el nodo. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param 
* @return Node* node
*/
Node * node_ini(){
	Node* node;

	node = (Node*) malloc (sizeof(Node));

	if(node == NULL)
		return NULL;

	node->id = 0;
	node->name = NULL;

	return node;
}

/**
* @brief Setea la id del nodo 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @param int id
* @return Node* n
*/
Node * node_setId(Node * n, const int id){

	if(n == NULL)
		return NULL;

	n->id = id;

	return n;
}

/**
* @brief Compara los nodos pasados por argumento y devuelve la diferencia de ids.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n1
* @param Node* n2
* @return int 
*/
int node_cmp (const Node * n1, const Node * n2){

	if(n1 == NULL)
		return -1;

	if(n2 == NULL)
		return -1;

	if(n1->id == n2->id)
		return strcmp(n1->name, n2->name);

	else if(n1->id < n2->id)
		return (n1->id - n2->id);

	else
		return (n1->id - n2->id);

}

/*************************************************************************************************************************************/

/**
* @brief Destruye el nodo
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @return 
*/
void node_destroy(Node *n){
  if (n == NULL) {
    return;
  }

  free(n);

  return;
}

/**
* @brief Coge la id del nodo 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @return int n->id
*/
int node_getId(const Node * n){
  if(n == NULL){
    return -1;
  }

  return n->id;
}

/**
* @brief Coge el nombre del nodo. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @return char* n->name
*/
const char* node_getName(const Node * n){
  if (n == NULL){
    return NULL;
  }

  return (char*)n->name;
}

/**
* @brief Setea el nombre dado al nodo. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @param char* name
* @return Node* n
*/
Node * node_setName(Node * n, char* name){
  if(n == NULL){
    return NULL;
  }

  n->name = name;

  return n;
}

/**
* @brief Copia el nodo pasado por argumento.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* src
* @return Node* aux
*/
Node *node_copy(const Node *src){
  Node *aux;

  aux = node_ini();

 aux->name = src->name;
  aux->id = src->id;

  return aux;
}

/**
* @brief Imprime el nodo y devuelve el numero de bytes impresos.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param FILE* pf
* @param Node* n
* @return int
*/
int node_print(FILE *pf, const Node *n){
  if(pf == NULL || n == NULL){
    return -1;
  }

  return fprintf(pf, "[%s, %d]", node_getName(n), node_getId(n));
}

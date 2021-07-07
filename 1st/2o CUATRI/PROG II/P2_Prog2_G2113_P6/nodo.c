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
	char name[TAM];
	int id;
	int nConnect;

	Label etq;
	int antecesor_id;
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
	node->nConnect = 0;
	node->name[0] = '\0';

	node->antecesor_id = 0;

	node->etq = BLANCO;

	return node;
}

/**
* @brief Coge el numero de conexiones del nodo 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @return int n->nConnect
*/
int node_getConnect(const Node * n){
	if(n == NULL)
		return -1;

	return n->nConnect;
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
* @brief Setea la conexión del nodo 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @param int cn
* @return Node* n
*/
Node * node_setConnect(Node * n, const int cn){

	if(n == NULL)
		return NULL;

	n->nConnect = cn;

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

  return n->name;
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
Node * node_setName(Node * n, const char* name){
  if(n == NULL){
    return NULL;
  }

  strcpy(n->name, name);

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

  strcpy(aux->name, src->name);
  aux->id = src->id;
  aux->nConnect = src->nConnect;
  node_setEtq(aux, src->etq);
  aux->antecesor_id = src->antecesor_id;

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

  return fprintf(pf, "[%s, %d, %d]", node_getName(n), node_getId(n), node_getConnect(n));
}

/**
* @brief Setea la etiqueta del nodo
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @param label etiqueta
* @return OK todo correcto
*         ERROR algun error
*/
Status node_setEtq(Node * n, Label etiqueta){

	if(n == NULL){
		return ERROR;
	}

	n->etq = etiqueta;

	return OK;
}

/**
* @brief Setea la id del antecesor.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @param int id
* @return OK todo correcto
*         ERROR algun error
*/
Status node_setAntecesor(Node * n, int id){
	if(n == NULL){
		return ERROR;
	}

	n->antecesor_id = id;

	return OK;
}

/**
* @brief Coge la etiqueta del nodo. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @return Label n->etq
*/
Label node_getEtq(const Node * n){
  if (n == NULL){
    return -1;
  }

  return n->etq;
}

/**
* @brief Coge la id del nodo antecesor. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Node* n
* @return int n->antecesor_id
*/
int node_getAntecesor(const Node * n){
  if (n == NULL){
    return -1;
  }

  return n->antecesor_id;
}
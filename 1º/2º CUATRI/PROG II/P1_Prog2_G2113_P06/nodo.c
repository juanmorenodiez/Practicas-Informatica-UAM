#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo.h"

#define TAM 100


struct _Node{
	char name[TAM];
	int id;
	int nConnect;
};

Node * node_ini(){
	Node* node;

	node = (Node*) malloc (sizeof(Node));

	if(node == NULL)
		return NULL;

	node->id = 0;
	node->nConnect = 0;
	node->name[0] = '\0'; 

	return node;
}

int node_getConnect(const Node * n){
	if(n == NULL)
		return -1;

	return n->nConnect;
}

Node * node_setId(Node * n, const int id){

	if(n == NULL)
		return NULL;

	n->id = id;

	return n;
}

Node * node_setConnect(Node * n, const int cn){

	if(n == NULL)
		return NULL;

	n->nConnect = cn;

	return n;
}

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

void node_destroy(Node *n){
  if (n == NULL) {
    return;
  }

  free(n);
}

int node_getId(const Node * n){
  if(n == NULL){
    return -1;
  }

  return n->id;
}

const char* node_getName(const Node * n){
  if (n == NULL){
    return NULL;
  }

  return n->name;
}

Node * node_setName(Node * n, const char* name){
  if(n == NULL){
    return NULL;
  }

  strcpy(n->name, name);

  return n;
}
Node *node_copy(const Node *src){
  Node *aux;

  aux = node_ini();

  strcpy(aux->name, src->name);
  aux->id = src->id;
  aux->nConnect = src->nConnect;

  return aux;
}

int node_print(FILE *pf, const Node *n){
  if(pf == NULL || n == NULL){
    return -1;
  }

  return fprintf(pf, "[%d, %s, %d]", n->id, n->name, n->nConnect);
}
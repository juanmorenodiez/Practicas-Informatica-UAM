/** 
 * @brief Define el elemento de nodos
 * 
 * @file stack_elestack.c
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0 
 * @date 12-03-2019
 * @copyright GNU Public License
 */
#include "elestack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "elestack.h"
#include "nodo.h"

struct _EleStack {
  Node* info;
};

/**
* @brief Crea el elemento 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param 
* @return Elestack* eles
*/
EleStack * EleStack_ini() {
  EleStack *eles;

  eles = (EleStack*)malloc(sizeof(EleStack));

  if (eles == NULL) {
    return NULL;
  }

  eles->info = NULL;

  return eles;
}

/**
* @brief Destruye el elemento 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Elestack* eles
* @return 
*/
void EleStack_destroy(EleStack *eles) {
  if (eles == NULL) {
    return;
  }

  node_destroy(eles->info);
  free(eles);

  return ;
}

/**
* @brief Setea la info del elemento
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Elestack* eles 
* @param void* info
* @return OK si todo correcto
*         ERRROR si hay algún error
*/
Status EleStack_setInfo(EleStack *eles, void *info) {
  Node *n = NULL;

  if (eles == NULL) {
    return ERROR;
  }

  if(eles->info != NULL){
    node_destroy(eles->info);
    eles->info = NULL;
  }

  n = node_copy(info);

  if (n == NULL) {
    return ERROR;
  }

  eles->info = n;
  

  return OK;

}

/**
* @brief Coge la info del elemento
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Elestack* eles
* @return (void*) eles->e
*/
void * EleStack_getInfo(const EleStack *eles) {
  if (eles == NULL) {
    return NULL;
  }

  return (void*)eles->info;
}

/**
* @brief Copia el elemento pasado por argumento
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Elestack* eles
* @return Elestack* eles
*/
EleStack * EleStack_copy(const EleStack *eles) {
  EleStack *copy = NULL;

  if (eles == NULL) {
    return NULL;
  }

  copy = EleStack_ini();

  if (copy == NULL) {
    return NULL;
  }

  copy->info = node_copy(eles->info);

  return copy;
}

/**
* @brief Comparar los elementos pasados por argumentos 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Elestack* eles1
* @param Elestack* eles2
* @return TRUE si son iguales
*         FALSE si son distintos
*/
Bool EleStack_equals(const EleStack *eles1, const EleStack *eles2) {
  if (eles1 == NULL || eles2 == NULL) {
    return FALSE;
  }

  if(node_getId(eles1->info) == node_getId(eles2->info)){
    return TRUE;
  }

  return FALSE;

}

/**
* @brief Imprime el elemento y devuelve el numero de bytes
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param FILE* pf
* @param Elestack* eles
* @return int bytes
*/
int EleStack_print(FILE *pf, const EleStack *eles) {
  int bytes=0;

  if (pf == NULL || eles == NULL) {
    return -1;
  }

  bytes = node_print(pf, (Node*)EleStack_getInfo(eles));

  return bytes;
}

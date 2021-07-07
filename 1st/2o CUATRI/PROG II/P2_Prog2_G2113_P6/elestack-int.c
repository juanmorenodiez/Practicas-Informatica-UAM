/** 
 * @brief Define el elemento de enteros
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

struct _EleStack {
  int* e;
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

  eles->e = NULL;

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

  free(eles->e);

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
  if (eles == NULL) {
    return ERROR;
  }

  if(eles->e == NULL){
    eles->e = (int*) malloc (sizeof(int));

    if(!eles->e){
      return ERROR;
    }
  }

  *eles->e = *(int*)info;

  return OK;

}

/**
* @brief Coge la info del elemento
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Elestack* eles
* @return int eles->e
*/
void * EleStack_getInfo(const EleStack *eles) {
  if (eles == NULL) {
    return NULL;
  }

  return eles->e;
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

  EleStack_setInfo(copy, eles->e);

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

  if(eles1->e == eles2->e){
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

  bytes = fprintf(stdout, "[%d]", *(int*)EleStack_getInfo(eles));

  return bytes;
}

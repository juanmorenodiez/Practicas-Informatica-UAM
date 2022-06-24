/** 
 * @brief Define la pila de elementos
 * 
 * @file stack_elestack.c
 * @author Camilo Jené Conde y Juan Moreno Diez 
 * @version 1.0 
 * @date 12-03-2019
 * @copyright GNU Public License
 */
#include "elestack.h"
#include "stack_elestack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXSTACK 1024

struct _Stack {
  int top;
  EleStack *item[MAXSTACK];
};

/**
* @brief Crea la pila. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param 
* @return Stack* ps
*/
Stack *stack_ini(){
  Stack *ps;
  int i;

  ps = (Stack*)malloc(sizeof(Stack));

  if (ps == NULL) {
    return NULL;
  }

  for (i=0; i < MAXSTACK; i++) {
    ps->item[i] = NULL;
  }

  ps->top = 0;

  return ps;
}

/**
* @brief Destruye la pila y sus elementos. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Stack* s
* @return 
*/
void stack_destroy(Stack *s) {
  int i;

  if (s == NULL) {
    return;
  }

  for (i=0; i < MAXSTACK; i++) {
    EleStack_destroy(s->item[i]);
  }

  free(s);

  return;
}

/**
* @brief Introduce un elemento en lo alto de la pila.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Stack* s
* @param Elestack* eles
* @return OK todo correcto
*         ERROR algun error
*/
Status stack_push(Stack *s, const EleStack *eles) {
  EleStack *es=NULL;

  if (s == NULL || eles == NULL || stack_isFull(s) == TRUE) {
    return ERROR;
  }

  es = EleStack_copy(eles);

  if (es == NULL) {
    return ERROR;
  }

  s->item[s->top] = es;

  s->top++;

  
  return OK;
}

/**
* @brief Extrae de la pila el elemento más alto.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Stack* s
* @return Elestack* es
*/
EleStack * stack_pop(Stack *s) {
  EleStack *es = NULL;

  if (s == NULL || stack_isEmpty(s) == TRUE) {
    return NULL;
  }

  s->top--;

  es = s->item[s->top];
  s->item[s->top] = NULL;

  return es;

}

/**
* @brief Comprueba si la pila está vacía.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Stack* s
* @return TRUE si está vacía
*         FALSE si tiene al menos un elemento
*/
Bool stack_isEmpty(const Stack *s) {
  if (s == NULL) {
    return FALSE;
  }

  if (s->top == 0) {
    return TRUE;
  }

  return FALSE;
}

/**
* @brief Comprueba si la pila está llena.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Stack* s
* @return TRUE si está llena
*         FALSE si hay al menos un espacio
*/
Bool stack_isFull(const Stack *s) {
  if (s == NULL) {
    return FALSE;
  }

  if(s->top == MAXSTACK + 1) {
    return TRUE;
  }

  return FALSE;
}

/**
* @brief Imprime la pila y devuelve el número de bytes.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param FILE* pf
* @param Stack* s
* @return int bytes
*/
int stack_print(FILE *pf, const Stack *s) {
  int bytes=0, i;

  if (pf == NULL || s == NULL) {
    return -1;
  }

  if (stack_isEmpty(s) == TRUE) {
    return bytes;
  }

  for (i=(s->top); i >= 0; i--) {
    bytes += EleStack_print(pf, s->item[i]);
    fprintf(stdout,"\n");
  }

  return bytes;
}

/**
* @brief Crea la media de los elementos de la pila y la devuelve.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Stack* stack
* @param char* argv[]
* @return double media
*/
double stack_media(Stack* stack, char* argv[]){
  int entero = 0;
  double media = 0;
  EleStack* eles = NULL;

  if(!stack){
    return -1;
  }

  if(stack_isEmpty(stack) == TRUE){
    return 0;
  }

  while(stack_isEmpty(stack) == FALSE){
    eles = stack_pop(stack);
    entero += *(int*)EleStack_getInfo(eles);
    EleStack_print(stdout, eles);
    fprintf(stdout, "\n");
    EleStack_destroy(eles);
  }


  media = entero/(atof(argv[1])+1);

  return media;
}
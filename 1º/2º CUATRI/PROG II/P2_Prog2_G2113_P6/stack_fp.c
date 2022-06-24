/** 
 * @brief Define la pila de elementos diferentes.
 * 
 * @file stack_elestack.c
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0 
 * @date 12-03-2019
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "stack_fp.h"

#define MAXSTACK 4096
#define EMPTY_STACK -1

extern int errno;

struct _Stack {
	int top;
	void * item[MAXSTACK];

	P_stack_ele_destroy pf_destroy;
	P_stack_ele_copy pf_copy;
	P_stack_ele_print pf_print;
	};

/**
* @brief Crea la pila con diferentes funciones.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param P_stack_ele_destroy fd
* @param P_stack_ele_copy fc
* @param P_stack_ele_print fp
* @return Stack* s
*/
Stack *stack_ini (P_stack_ele_destroy fd, P_stack_ele_copy fc, P_stack_ele_print fp) {
	Stack *s;
	int i;

	s = (Stack*) malloc(sizeof(Stack));

	if (!s) {
		fprintf(stderr, "%s", strerror(errno));
		return NULL;
	}

	/* Inicializo tope y asigno los punteros a función */
	s->top = -1;
	s->pf_copy = fc;
	s->pf_destroy = fd;
	s->pf_print = fp;

	/* Asigno los punteros de los elementos */
	for (i=0; i< MAXSTACK; i++){
		s->item[i] = NULL;
	}

	return s;
}

/**
* @brief Destruye la pila y sus elementos. 
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Stack* s
* @return 
*/
void stack_destroy(Stack* stc) {
	if (!stc) {
		return;
	}

	while (stc->top != EMPTY_STACK) {
		stc->pf_destroy(stc->item[stc->top]); /* Llamada a la función cuyo puntero se almacenó como campo
											    de la pila, es decir, utilizando el puntero a la función */
		stc->top --;
	}

	free(stc);
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
Status stack_push(Stack *s, const void *eles){
	void* aux = NULL;

	if(!s || !eles){
		return ERROR;
	}

	if (stack_isFull(s) == TRUE) {
    	return ERROR;
  	}

	aux = s->pf_copy(eles);

	if(!aux){
		return ERROR;
	}

	s->top++;

	s->item[s->top] = aux;

	return OK;
}

/**
* @brief Extrae el último elemento de la pila.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Stack* s
* @return void* aux
*/
void * stack_pop(Stack * s){
	void* aux = NULL;

	if(!s){
		return NULL;
	}

	if (stack_isEmpty(s) == TRUE) {
    	return NULL;
  	}

	aux = s->item[s->top];
	s->item[s->top] = NULL;
	s->top--;

	return aux;
}

/**
* @brief Informa de si la pila está vacía.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Stack* s
* @return TRUE si está vacía.
*         FALSE si no lo está o hay algún error.
*/
Bool stack_isEmpty(const Stack *s){
	if(!s){
		return FALSE;
	}

	if(s->top == -1){
		return TRUE;
	}else{
		return FALSE;
	}
}

/**
* @brief Informa de si la pila está LLENA.
* @date 12/03/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Stack* s
* @return TRUE si está llena.
*         FALSE si no lo está o hay algún error.
*/
Bool stack_isFull(const Stack *s){
	if(!s){
		return FALSE;
	}

	if(s->top == MAXSTACK){
		return TRUE;
	}else{
		return FALSE;
	}
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
int stack_print(FILE *pf, const Stack *s) {
  int bytes = 0, i;

  if (pf == NULL || s == NULL) {
    return -1;
  }

  if (stack_isEmpty(s) == TRUE) {
    return bytes;
  }

  for (i=(s->top); i >= 0; i--) {
    bytes += s->pf_print(pf, s->item[i]);
    fprintf(stdout, "\n");
  }

  return bytes;
}


/** 
 * @brief Define la interfaz de stack_elestack.c
 * for each command
 * 
 * @file stack_elestack.h
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0 
 * @date 12-03-2018 
 * @copyright GNU Public License
 */
#ifndef STACK_H
#define STACK_H

#include "elestack.h"

typedef struct _Stack Stack;

/**------------------------------------------------------------------
Inicializa la pila reservando memoria. Salida: NULL si ha habido error oel puntero ala pila si ha ido bien
------------------------------------------------------------------*/
Stack * stack_ini();

/**------------------------------------------------------------------
Elimina la pila Entrada: puntero a la pila que se desea eliminar
------------------------------------------------------------------*/
void stack_destroy(Stack *);

/**------------------------------------------------------------------
Inserta un elemento en la pila. Entrada: elemento a insertar y pila donde insertarlo. Salida: OK si logra insertarlo o ERROR si no.
------------------------------------------------------------------*/
Status stack_push(Stack *, const EleStack *);

/**------------------------------------------------------------------
Extrae un elemento de la pila. Entrada: la pila de donde extraerlo. Salida: NULL si no logra extraerlo,o el elemento
extraído si lo logra. Nótese que la pila quedará modificada.
------------------------------------------------------------------*/
EleStack * stack_pop(Stack *);

/**------------------------------------------------------------------
Comprueba si la pila esta vacía. Entrada: puntero a la pila. Salida: TRUE si está vacíao FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *);

/**------------------------------------------------------------------
Comprueba si la pila esta llena. Entrada: puntero a la pila. Salida: TRUE si está llena o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isFull(const Stack *);

/**------------------------------------------------------------------Imprime toda la pila, comenzando por el último elemento insertado (aquel en la cima o tope) y terminando por el primero
que se insertó. Imprime un elemento por línea. Entrada: pila y fichero abierto donde imprimir. Salida: número de
 caracteres escritosen total.
 ------------------------------------------------------------------*/
 int stack_print(FILE*, const Stack*);

 double stack_media(Stack* stack, char* argv[]);

 #endif

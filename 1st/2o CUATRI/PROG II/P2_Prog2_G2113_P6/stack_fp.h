#ifndef STACK_H
#define STACK_H
#include "types.h"

typedef struct _Stack Stack;

/* Tipos de los punteros a función soportados por la pila */
typedef void (*P_stack_ele_destroy)(void*);
typedef void* (*P_stack_ele_copy)(const void*);
typedef int (*P_stack_ele_print)(FILE *, const void*);

/* La función stack_ini recibirá los valores para los campos de la pila que son punteros a función, es decir, recibirá las
funciones para, respectivamente, destruir, copiar e imprimir los elementos de la pila creada*/
Stack * stack_ini (P_stack_ele_destroy f1, P_stack_ele_copy f2, P_stack_ele_print f3);
void stack_destroy(Stack *);
Status stack_push(Stack *, const void *);
void * stack_pop(Stack *);
Bool stack_isEmpty(const Stack *);
Bool stack_isFull(const Stack *);
int stack_print(FILE*, const Stack*);

#endif
/**
 * @brief Define la interfaz de queuel.c
 * for each command
 *
 * @file queuel.h
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0
 * @date 15-04-2019
 * @copyright GNU Public License
 */

#ifndef QUEUEL_H
#define QUEUEL_H

#include "types.h"
#include "nodo.h"
#include "list.h"

typedef struct _Queue Queue;

/* Tipos de los punteros a función soportados por la cola.
Nota: podrían estar en elem_functions.h e incluirlo aquí */

typedef void (*destroy_element_function_type1)(void*);
typedef void (*(*copy_element_function_type1)(const void*));
typedef int (*print_element_function_type1)(FILE *, const void*);
/**------------------------------------------------------------------

Inicializa la cola: reserva memoria para ella e inicializa todos sus elementos a NULL.
------------------------------------------------------------------*/
Queue* queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3);
/**------------------------------------------------------------------
Libera la cola, liberando todos sus elementos.
------------------------------------------------------------------*/
void queue_destroy(Queue *q);
/**------------------------------------------------------------------
Comprueba si la cola está vacía.
------------------------------------------------------------------*/
Bool queue_isEmpty(const Queue *q);
/**------------------------------------------------------------------
Comprueba si la cola está llena.
------------------------------------------------------------------*/
Bool queue_isFull(const Queue* queue);
/**------------------------------------------------------------------
Inserta un nuevo nodo en la cola, reservando memoria nueva para él y haciendo una copia del elemento recibido.
------------------------------------------------------------------*/
Status queue_insert(Queue *q, const void* pElem);
/**------------------------------------------------------------------
Extrae un elemento de la cola. Devuelve directamente el puntero al elemento (no hace copia).
------------------------------------------------------------------*/
void * queue_extract(Queue *q);
/**------------------------------------------------------------------
Devuelve el número de elementos de la cola.
------------------------------------------------------------------*/
int queue_size(const Queue *q);
/**------------------------------------------------------------------
Imprime toda la cola, devolviendo el número de caracteres escritos.
------------------------------------------------------------------*/
int queue_print(FILE *pf, const Queue *q);

#endif

/**
 * @brief Define el TAD de una cola
 * implementada con lista
 *
 * @file queuel.c
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0
 * @date 15-04-2019
 * @copyright GNU Public License
 */

#include "queuel.h"

struct _Queue {
  List *list;

  destroy_element_function_type1 destroy_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
};

/**
* @brief crea e inicializa una cola implementada
* con lista
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param f1
* @param f2
* @param f3
* @return Queue *q
*/

Queue* queue_ini(destroy_element_function_type1 f1, copy_element_function_type1 f2, print_element_function_type1 f3) {
  Queue *q;

  q = (Queue*)malloc(sizeof(Queue));

  if (q == NULL) {
    return NULL;
  }

  q->destroy_element_function = f1;
  q->copy_element_function = f2;
  q->print_element_function = f3;

  q->list = list_ini((destroy_element_function_type)f1, (copy_element_function_type)f2, (print_element_function_type)f3, (cmp_element_function_type)node_cmp);
  if (q->list == NULL) {
    free(q);
    return NULL;
  }

  return q;
}

/**
* @brief destruye una cola implementada
* con lista
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Queue *q
* @return
*/

void queue_destroy(Queue *q) {
  if (q == NULL) {
    return;
  }

  list_destroy(q->list);
  free(q);
}

/**
* @brief comprueba si una cola esta vacia
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param const Queue *q
* @return Bool, segun la cola este vacia
* o no.
*/

Bool queue_isEmpty(const Queue *q) {
  if (q == NULL) {
    return TRUE;
  }

  return list_isEmpty(q->list);
}

/**
* @brief comprueba si una cola esta vacia
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param const Queue *queue
* @return Bool, segun la cola este vacia
* o no.
*/

Bool queue_isFull(const Queue* queue) {
  if (queue == NULL) {
    return FALSE;
  }

  return TRUE;
}

/**
* @brief inserta un elemento en una cola implementada
* con lista
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Queue *q
* @param const void *pElem
* @return OK si la insercion se ha podido realizar,
* ERROR si se ha producido algun error.
*/

Status queue_insert(Queue *q, const void* pElem) {
  if (q == NULL || pElem == NULL) {
    return ERROR;
  }

  if (list_insertLast(q->list, pElem) == ERROR) {
    return ERROR;
  }

  return OK;
}

/**
* @brief extrae un elemento en una cola implementada
* con lista
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Queue *q
* @return void *elem
*/

void * queue_extract(Queue *q) {
  void *elem = NULL;

  if (q == NULL) {
    return NULL;
  }

  elem = list_extractFirst(q->list);

  return elem;
}

/**
* @brief devuelve el tamanio de una cola
* implementada con una lista
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param const Queue *q
* @return list_size(q->list)
*/

int queue_size(const Queue *q) {
  if (q == NULL) {
    return -1;
  }

  return list_size(q->list);
}

/**
* @brief imprime el numero de caracteres almacenados
* en una cola implementada con lista
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param FILE *pf
* @param const Queue *q
* @return int bytes
*/

int queue_print(FILE *pf, const Queue *q) {
  int bytes = 0;

  if (pf == NULL || q == NULL) {
    return -1;
  }

  if (list_isEmpty(q->list) == TRUE) {
    return 0;
  }

  bytes = list_print(pf, q->list);

  return bytes;
}

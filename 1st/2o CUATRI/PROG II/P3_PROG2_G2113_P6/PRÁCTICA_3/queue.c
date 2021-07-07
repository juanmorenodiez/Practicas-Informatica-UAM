/**
 * @brief Define el TAD de cola
 *
 * @file queue.c
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0
 * @date 15-04-2019
 * @copyright GNU Public License
 */

#include "queue.h"

#define MAX_QUEUE 1024

struct _Queue {
  void *items[MAX_QUEUE];
  int front;
  int rear;

  destroy_element_function_type destroy_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
};

/**
* @brief crea e inicializa una cola
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param f1
* @param f2
* @param f3
* @return Queue *q
*/

Queue* queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3) {
  Queue *q;
  int i;

  q = (Queue*)malloc(sizeof(Queue));

  if (q == NULL) {
    return NULL;
  }

  q->destroy_element_function = f1;
  q->copy_element_function = f2;
  q->print_element_function = f3;

  for (i=0; i < MAX_QUEUE; i++) {
    q->items[i] = NULL;
  }

  q->front = 0;
  q->rear = 0;

  return q;
}

/**
* @brief destruye una cola
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Queue *q
* @return
*/

void queue_destroy(Queue *q) {
  int i;

  if(q != NULL) {
    i = q->front;
    while(i != q->rear) {
      q->destroy_element_function(q->items[i]);
      q->items[i] = NULL;
      i = (i+1) % MAX_QUEUE;
    }
    free(q);
  }

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

  if (q->front == q->rear) {
    return TRUE;
  }

  return FALSE;
}

/**
* @brief comprueba si una cola esta llena
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param const Queue *queue
* @return Bool, segun la cola este llena
* o no.
*/

Bool queue_isFull(const Queue* queue) {
  if (queue == NULL) {
    return FALSE;
  }

  if (queue->front == (queue->rear+1) % MAX_QUEUE) {
    return TRUE;
  }
  return FALSE;
}

/**
* @brief inserta un elemento en una cola
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Queue *q
* @param const void *pElem
* @return OK si la insercion se ha podido realizar,
* ERROR si se ha producido algun error.
*/

Status queue_insert(Queue *q, const void* pElem) {
  Node *pn = NULL;

  if (q == NULL || pElem == NULL) {
    return ERROR;
  }

  pn = q->copy_element_function(pElem);

  if (pn == NULL) {
    return ERROR;
  }

  q->items[q->rear] = pn;

  q->rear = (q->rear+1) % MAX_QUEUE;

  return OK;
}

/**
* @brief extrae un elemento de una cola
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param Queue *q
* @return void *ele
*/

void * queue_extract(Queue *q) {
  void *ele = NULL;

  if (q == NULL) {
    return NULL;
  }

  ele = q->items[q->front];

  q->items[q->front] = NULL;

  q->front = (q->front+1) % MAX_QUEUE;

  return ele;
}

/**
* @brief devuelve el tamanio de una cola
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param const Queue *q
* @return int contador(tamanio de la cola)
*/

int queue_size(const Queue *q){
  int contador = 0, i = 0;

  if(!q){
    return -1;
  }

  for(i=0; i < MAX_QUEUE; i++){
    if(q->items[i] != NULL){
      contador++;
    }
  }

  return contador;
}

/**
* @brief devuelve el numero de caracteres impresos
* de una cola
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param FILE *pf
* @param const Queue *q
* @return int bytes
*/

int queue_print(FILE *pf, const Queue *q){
  int bytes = 0, i = 0;
  if(!pf || !q){
    return -1;
  }

  if(queue_isFull(q) == TRUE){
    return bytes;
  }

  for(i = 0 ; i < MAX_QUEUE ; i++){
    if(q->items[i] != NULL){
      bytes = q->print_element_function(pf, q->items[i]);
    }
  }

  return bytes;
}

/*
@fichero: ejercicio2.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 05/03/2019
@descripción: programa que prueba el envío de
señales mediante el uso de procesos.
*/

typedef struct _Queue Queue;

Queue *queue_create();
boolean queue_is_empty(Queue *q);
boolean queue_is_full(Queue *q);
void queue_insert(Queue *q,char c);
int queue_extract(Queue *q);

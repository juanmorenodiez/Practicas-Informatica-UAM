#include <stdio.h>
#include "queue.h"
#define SIZE 10


struct Queue {
   int front
	 int rear;
   char *info;
};

Queue *queue_create() {
   Queue *q=(Queue *) malloc (sizeof(Queue));
	 if (q == NULL){
		 perror ("Initializing queue");
		 return NULL
	 }

   q->front=-1;
   q->rear=-1;
   q->info = (char *) malloc (SIZE*sizeof(char));
   if (q->info == NULL){
		 perror("Error initializing memory for characters")
		 return NULL;
	 }
	 return q;
}

boolean queue_is_empty(Queue *q) {
	if (q->front==-1)
		return true;
	return false;
}

boolean queue_is_full(Queue *q) {
	if ((q->rear+1) % SIZE == q->rear)
		 	return true;
	return false;
}

int queue_size(Queue *q) {
   return (SIZE - q->rear + q->front+1) % SIZE;
}


void queue_insert(Queue *q,char c) {

   if(queue_is_full(q)){
		 perror ("Queue is full");
		 return;
	 }

   else{
      q->rear = (q->rear+1) % SIZE;
      q->info[q->rear] = c;

      if(q->front==-1) {
         q->front=q->rear;
      }
   }
}

int queue_extract(Queue *q) {
   char c;

	 if(queue_is_empty(q)) {
      perror("Queue is empty");
      return 0;
   }

   else {
      c=q->info[q->front];

      if(q->front==q->rear)
         q->front=q->rear=-1;

			else
         q->front=(q->front+1)%SIZE;
   }

   return c;
}

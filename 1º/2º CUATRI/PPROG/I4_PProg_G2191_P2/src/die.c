#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "die.h"

/**
* @brief die with id and last number
*
* Struct for storing a die that will show a random number
* and get the last roll.
*/

struct _Die{

  Id id;  /*!< id (long int) */
  int lastroll;  /*!< last roll of the die(int) */

};

Die *die_create(Id id){

  Die *d=NULL;

  d=(Die *) calloc(1,sizeof(Die));

  d->id=id;
  d->lastroll=0;
  
  return d;
}

void die_destroy(Die *d){

  free(d);
  
}

int die_get_lastroll(Die *d){

  return d->lastroll;
}

Id die_get_id(Die *d) {

  return d->id;
}

STATUS die_roll(Die *d){
    
  if(!d) return ERROR;

   d->lastroll = rand() % 6+1;
  
  return OK;
}

void die_print_content(Die *d){

  if(!d) return;

  fprintf(stdout,"%d\n",die_get_lastroll(d));
}

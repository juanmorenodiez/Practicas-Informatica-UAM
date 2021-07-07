#include <stdio.h>
#include <stdlib.h>
#include "set.h"

#define MAXSET 16   /*!< defines max number of sets */

/**
* @brief id and number of ids
*
* Struct for managing the values and adding ids
* by using an id and the number of ids.
*/

struct _Set{

  Id ids[MAXSET];    /*!< id (long int) */
  int nids;    /*!< number of ids */

};

Set *set_create(){
	
  Set *set=NULL;
	
  set=(Set *) calloc(1, sizeof(Set));
  set->nids=-1;	

  return set;
}

int set_get_nids(Set * set){
  return set->nids; 
}


void set_destroy(Set * set){

  if(set!=NULL) free(set);

}

STATUS set_add_value(Id id, Set *set){

  if(!set || !id) return ERROR;
  
  set->nids++;
  set->ids[set->nids]= id;

  return OK;

}

STATUS set_delete_value(Id id, Set *set){

  int i;
  int aux;
  if(!set || !id) return ERROR;

  for(i=0;i<set->nids;i++){
		
    if(set->ids[i]==id){
      aux = i;
    }
  }
  for(i=0; i<set->nids-1; i++){
  
    if(i>=aux){

    set->ids[i] = set->ids[i + 1];

    }

  }
  
  set->nids--;
  return OK;
}

Id get_set(Set *set, int position){
  if (set==NULL)
    return NO_ID;

  return set->ids[position];
}

BOOL set_has_id(Set *set, Id id){
  int i;
  
  if(!set) return FALSE;
  
  for(i=0; i<MAXSET; i++){
    if(get_set(set, i)==id)
      return TRUE;
    
  }
  return FALSE;
}

void set_print_values(Set *set){

  int i;
  
  for(i=0;i<(set->nids + 1);i++){

    fprintf(stdout,"[%ld]\n", set->ids[i]);
  
  }
  fprintf(stdout,"Number of ids in the set: %d\n",set->nids+1);

}

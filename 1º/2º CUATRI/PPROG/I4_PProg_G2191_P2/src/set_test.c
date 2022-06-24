#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "set.h"

int main(){

  Set *set=NULL;
  Id id=NO_ID;
  Id id2 = NO_ID;
  set=set_create();
  if(set!=NULL) 
    printf("Set created.\n");

  printf("Introduce an id:");
  scanf("%ld", &id2);
  
  if(set_add_value(id2,set)==ERROR) return 1;
  else printf("Id added to the set.\n");
  set_print_values(set);
  

  printf("Introduce otra id:");
  scanf("%ld", &id);
  
  if(set_add_value(id,set)==ERROR) return 1;
  else printf("Id added to the set.\n");
  set_print_values(set);


  if(set_delete_value(id2, set)==ERROR) return 1;
  printf("Id deleted from the set.\n");
  set_print_values(set);
  set_destroy(set);
  if(set==NULL)
    fprintf(stdout,"There are no ids.");
   

  return 0;
}

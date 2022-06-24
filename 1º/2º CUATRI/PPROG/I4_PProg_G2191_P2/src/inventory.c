#include <stdio.h>
#include <stdlib.h>

#include "set.h"
#include "inventory.h"

/**
* @brief set and max objects.
*
* Struct for organising the objects using a pointer to set
* and a maximum number of objects(int).
*/

struct _Inventory{

  Set *objects;    /*!< set of ids */
  int num;    /*!< max number of objects */

};

Inventory* inventory_create() {

  Inventory *newInventory = NULL;

  newInventory = (Inventory *) malloc(sizeof(Inventory));

  if (newInventory == NULL) {
    return NULL;
  }
  newInventory->objects = set_create();

  newInventory->num = 0;
  
  return newInventory;
}

STATUS inventory_destroy(Inventory *inv){

  if(inv == NULL)
    return ERROR;
  
  set_destroy(inv->objects);
  free(inv);
  
  
  return OK;
}
   
STATUS inventory_add_id(Inventory *inv, Id id){

  if(id == NO_ID || inv == NULL)
    return ERROR;
  
  if(inv->num < 3){
    set_add_value(id, inv->objects);
    inv->num++;

    return OK;
  }
  
  return ERROR;
}

STATUS inventory_delete_id(Inventory *inv, Id id){

  if(id == NO_ID || inv == NULL) return ERROR;
   
  set_delete_value(id, inv->objects);
   
  return OK;
}

Id inventory_get_object(Inventory *inv, int position) {
  if (inv == NULL) {
    return NO_ID;
  }
  return get_set(inv->objects, position);
	
}

BOOL inventory_has_object(Inventory *inv, Id id){
  if(!inv || id == NO_ID) return FALSE;
  
  if(set_has_id(inv->objects, id)==FALSE)
    return FALSE;
  
  return TRUE;
}

Set *inventory_get_set(Inventory *inv){

  if(inv == NULL) return NULL;
  
  return inv->objects;
}

BOOL inventory_is_empty(Inventory *inv){
  if(!inv) return FALSE;
  
  if(inv->num==0) return TRUE;
  
  return FALSE;
  
}
BOOL inventory_is_full(Inventory *inv){
  if(!inv) return FALSE;
  
  if(inv->num==4) return TRUE;
  
  return FALSE;
  
}

STATUS inventory_print(Inventory *inv){

  if(inv == NULL) return ERROR;
  
  set_print_values(inv->objects);
  
  return OK;
}














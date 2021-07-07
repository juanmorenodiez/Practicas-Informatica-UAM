/**
* @brief Implements the game player commands
*
* The player will be the one doing every action, such
* as picking an object or moving to a certain parts. It
* is in charge of getting the commands done.
*
* @file player.c
* @author Borja Pérez
* @version 1.6
* @date 09-04-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "player.h"
#include "inventory.h"


/** The Player structure contains the player related information
    %Privacy: private structure                                  **/

/**
* @brief player definition
*
* Struct for storing a player and the elements
* it will use while playing.
*/

struct _Player{

  Id id;  /*!< Player Identifier ingame */
  char name[MAXPLAYNAME];  /*!< Player name */
  Id location;  /*!< Additional ID, for saving the space where the player is located  */
  Inventory * carrying;  /*!< objects that player will carry */
};

Player * player_create(Id id){

  Player * p = NULL;

  p = (Player*) calloc(1, sizeof(Player));
  if(p==NULL) return NULL;

  p->carrying = inventory_create();
  p->id = id;
  p->location = 0;


  return p;
}

STATUS player_destroy(Player * p){

  if(!p) return ERROR;

  inventory_destroy(p->carrying);
  free(p);
  return OK;
}
char * player_get_name(Player * p){

  if(!p) return NULL;
  return p->name;
}

Id player_get_id(Player * p){

  if(!p) return NO_ID;
  return p->id;
}

Id player_get_location(Player * p){

  if(!p) return NO_ID;
  return p->location;
}

Id player_get_object(Player * p, int position){

  if(!p) return NO_ID;
  return inventory_get_object(p->carrying, position);
}

Inventory * player_get_inventory(Player * p){

  if(!p) return NULL;
  return p->carrying;
}

STATUS player_set_name(Player * p, char * name){

  if(!p) return ERROR;
  strcpy(p->name, name);
  return OK;
}

STATUS player_set_id(Player * p, Id id){

  if(!p) return ERROR;
  p->id = id;
  return OK;
}

BOOL player_has_id(Player *p, Id id){
  if(!p) return FALSE;

  if(inventory_has_object(p->carrying, id)==FALSE)
    return FALSE;

  return TRUE;
}

STATUS player_set_location(Player * p, Id location){

  if(!p) return ERROR;
  p->location = location;
  return OK;
}

STATUS player_set_object(Player * p, Id id){

  if(!p) return ERROR;
  if(inventory_add_id(p->carrying, id)==ERROR)
    return ERROR;

  return OK;
}

BOOL player_inventory_is_empty(Player *p){
  if(!p) return FALSE;
  if(inventory_is_empty(p->carrying)== TRUE) return TRUE;
  return FALSE;
}
BOOL player_inventory_is_full(Player *p){
  if(!p) return FALSE;
  if(inventory_is_full(p->carrying)== TRUE) return TRUE;
  return FALSE;
}

STATUS player_remove_object(Player *p, Id id){
  if (p==NULL || id==NO_ID) return ERROR;

  inventory_delete_id(p->carrying, id);
  return OK;

}

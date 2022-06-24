/**
* @brief Implements the game object commands
*
* The object module has all the functions that
* helps us manage the objects with a better
* organisation.
*
* @file object.c
* @author Juan Moreno
* @version 1.6
* @date 07-04-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"
#include "game.h"

/** The object structure places together the object id and name
    %Privacy: private structure                                 **/


/**
* @brief properties of the objects in the game
*
* Struct for storing the different properties that an object should have
*/
typedef struct{
  BOOL Movable; /*!<Movable property */
  BOOL Moved; /*!< Moved property */
  BOOL Hidden; /*!< Hidden property */
  Id Open; /*!< Id status */
  BOOL Illuminate; /*!< Iluminate property */
  BOOL SwitchedOn; /*!< SwitchedOn property */
}Objectproperties;


/**
* @brief object of the game
*
* Struct for storing the different variables that an object should have
*/

struct _Object{
  Id id; /*!< Object identifier */
  Id location;  /*!< Object location */
  Id initialpos;  /*!< Original object location */
  char name[MAXOBJNAME];  /*!< Object name to be shown ingame */
  char sdescription[MAX_DESCRIPTION];  /*!< Object description to be shown ingame (original) */
  char ldescription[MAX_DESCRIPTION];  /*!< Object description to be shown ingame (moved) */
  Objectproperties prop; /*!< Struct properties*/
};




Object * object_create(Id id){

  Object * o = NULL;
  o = (Object*) calloc(1, sizeof(Object));
  if(o==NULL) return NULL;

  o->id = id;
  o->location=NO_ID;
  o->initialpos=NO_ID;
	o->prop.Movable=FALSE;
  o->prop.Moved=FALSE;
  o->prop.Hidden=FALSE;
  o->prop.Open=NO_ID;
  o->prop.Illuminate=FALSE;
  o->prop.SwitchedOn=FALSE;

  return o;
}

void object_destroy(Object * o){
  if (o==NULL)
    return;
  free(o);
}

Id object_get_id(Object * o){

  if(o == NULL) return NO_ID;

  return o->id;

}

Id object_get_original_position(Object * o){

  if(o == NULL) return NO_ID;

  return o->initialpos;

}

Id object_get_location(Object * o){

  if(o == NULL) return NO_ID;

  return o->location;

}

char * object_get_name(Object * o){

  if(o == NULL) return NULL;

  return o->name;

}

char * object_get_original_description(Object * o){

  if(o == NULL) return NULL;

  return o->sdescription;

}

char * object_get_moved_description(Object * o){

  if(o == NULL) return NULL;

  return o->ldescription;

}

STATUS object_set_id(Object * o, Id id){

  if(o == NULL) return ERROR;

  o->id = id;

  return OK;
}

STATUS object_set_location(Object * o, Id id){

  if(o == NULL) return ERROR;

  o->location = id;

  return OK;
}

STATUS object_set_original_position(Object * o, Id id){

  if(o == NULL || id==NO_ID) return ERROR;

  o->initialpos = id;

  return OK;
}

STATUS object_set_name(Object * o, char * name){
  if(o == NULL || name == NULL)
    return ERROR;

  strcpy(o->name, name);

  return OK;
}

STATUS object_set_original_description(Object * o, char * description){
  if(o == NULL|| description == NULL)
    return ERROR;

  strcpy(o->sdescription, description);

  return OK;
}

STATUS object_set_moved_description(Object * o, char * description){
  if(o == NULL|| description == NULL)
    return ERROR;

  strcpy(o->ldescription, description);

  return OK;
}

STATUS object_set_prop_Movable(Object *o, BOOL st){

  if(o == NULL) return ERROR;

  o->prop.Movable = st;

  return OK;
}

BOOL object_get_prop_Movable(Object *o){

  if(o == NULL) return FALSE;

  return o->prop.Movable;
}


STATUS object_set_prop_Moved(Object *o, BOOL st){

  if(o == NULL) return ERROR;

  o->prop.Moved = st;

  return OK;
}

BOOL object_get_prop_Moved(Object *o){

  if(o == NULL) return FALSE;

  return o->prop.Moved;
}

STATUS object_set_prop_Hidden(Object *o, BOOL st){

  if(o == NULL) return ERROR;

  o->prop.Hidden = st;

  return OK;
}

BOOL object_get_prop_Hidden(Object *o){

  if(o == NULL) return FALSE;

  return o->prop.Hidden;
}

STATUS object_set_prop_Illuminate(Object *o, BOOL st){

  if(o == NULL) return ERROR;

  o->prop.Illuminate = st;

  return OK;
}

BOOL object_get_prop_Illuminate(Object *o){

  if(o == NULL) return FALSE;

  return o->prop.Illuminate;
}

STATUS object_set_prop_SwitchedOn(Object *o, BOOL st){

  if(o == NULL) return ERROR;

  o->prop.SwitchedOn = st;

  return OK;
}

BOOL object_get_prop_SwitchedOn(Object *o){

  if(o == NULL) return FALSE;

  return o->prop.SwitchedOn;
}

STATUS object_set_prop_Open(Object *o, Id id){

  if(o == NULL || id == NO_ID) return ERROR;

  o->prop.Open = id;

  return OK;
}

Id object_get_prop_Open(Object *o){

  if(o == NULL) return NO_ID;

  return o->prop.Open;
}


STATUS object_print(Object * o, FILE * f){

  if(o == NULL || f == NULL) return ERROR;
  fprintf(f, "%ld / %s" ,o->id, o->name);

  return OK;
}

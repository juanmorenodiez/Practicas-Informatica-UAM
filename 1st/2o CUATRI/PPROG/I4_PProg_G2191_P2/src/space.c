/**
* @brief Defines the space related functions
*
* Sets the new functionality of the space module
* that will allow is incorporate other new complements
* created.
*
* @file space.c
* @author Dan Roife
* @version 1.1
* @date 08-04-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "link.h"


/** The space structure codes the maps (saved in data.dat)
    %Privacy: private structure                            **/

/**
* @brief spaces of the game
*
* Struct for storing the different variables and
* characteristics that spaces should have.
*/



struct _Space {
  Id id;  /*!< Space identifier */
  char name[WORD_SIZE + 1];  /*!< Space name */
  Id north;  /*!< Id of the space located in the north */
  Id south;  /*!< Id of the space located in the south */
  Id east;  /*!< Id of the space located in the east */
  Id west;  /*!< Id of the space located in the west */
  Id up;  /*!< Id of the space located upwards */
  Id down;  /*!< Id of the space located downwards */
  Set * objects;  /*!< Object located in that space */
  char gdesc[30][110]; /*!< Graphic description */
  char sdescription[MAX_DESCRIPTION];  /*!< space description */
  char ldescription[MAX_LONG_DESCRIPTION];  /*!< space description */
  BOOL iluminate;  /*!< space ilumination properties */
};


char * space_get_gdesc_line(Space * s, int line){

  return s->gdesc[line];
}

STATUS space_set_gdesc_line(Space * s, int line, char * c){

  strcpy(s->gdesc[line], c);
  return OK;
}



Space* space_create(Id id) {

  Space *newSpace = NULL;

  if (id == NO_ID)
    return NULL;

  newSpace = (Space *) malloc(sizeof (Space));

  if (newSpace == NULL) {
    return NULL;
  }
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->up = NO_ID;
  newSpace->iluminate = FALSE;
  newSpace->down = NO_ID;

  newSpace->objects = set_create();

  return newSpace;
}

STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }
  set_destroy(space->objects);

  free(space);
  space = NULL;

  return OK;
}

STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }

  return OK;
}

STATUS space_set_short_description(Space* space, char* description) {
  if (!space || !description) {
    return ERROR;
  }

  if (!strcpy(space->sdescription, description)) {
    return ERROR;
  }

  return OK;
}

char * space_get_short_description(Space* space){
  if (!space) {
    return NULL;
  }
  return space->sdescription;
}


STATUS space_set_long_description(Space* space, char* description) {
  if (!space || !description) {
    return ERROR;
  }

  if (!strcpy(space->ldescription, description)) {
    return ERROR;
  }

  return OK;
}

char * space_get_long_description(Space* space){
  if (!space) {
    return NULL;
  }
  return space->ldescription;
}

STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

STATUS space_set_up(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->up = id;
  return OK;
}

STATUS space_set_down(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->down = id;
  return OK;
}

STATUS space_set_iluminate(Space *space, BOOL iluminate){
  if(space == NULL)
    return ERROR;

  space->iluminate= iluminate;

  return OK;
}

BOOL space_get_iluminate(Space *space){
  if(space == NULL)
    return FALSE;

  return space->iluminate;
}

STATUS space_set_object(Space* space, Object * o) {
  if (!space) {
    return ERROR;
  }
  set_add_value(object_get_id(o), space->objects);
  return OK;
}

int space_get_object_number(Space* space){
  if (space==NULL)
    return -1;
  return set_get_nids(space->objects);

}

const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

Id space_get_up(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->up;
}

Id space_get_down(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->down;
}

Set * space_get_object(Space* space) {
  if (!space) {
    return FALSE;
  }
  return space->objects;
}


STATUS space_object_destroy(Space * s, Id id){

  if(!s || !id) return ERROR;

  set_delete_value(id, s->objects);

  return OK;

}

STATUS space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  idaux = space_get_up(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Up link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No up link.\n");
  }

  idaux = space_get_down(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Down link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No down link.\n");
  }

  if (space_get_object(space)) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  if(space_get_iluminate(space) == TRUE){
    fprintf(stdout, "---> Space iluminated.\n");
  } else{
    fprintf(stdout, "---> Space not iluminated.\n");
  }

  return OK;
}



/*R5:Para determinar si un espacio está unido con otro a través de un enlace*/

/**
* @brief checks if space is linked
*
* It determines if a space is linked to another one
* by using the "link" module functions.
*
* @author Dan Roife
* @param s pointer to space.
* @return BOOL, FALSE if when checking is not correct, if
* it is correct, TRUE.
*/

BOOL space_is_linked(Space *s){

	if(!s) return FALSE;

	if(s->north != NO_ID) return TRUE;
	else return FALSE;

	if(s->south != NO_ID) return TRUE;
	else return FALSE;

	if(s->east != NO_ID) return TRUE;
	else return FALSE;

	if(s->west != NO_ID) return TRUE;
	else return FALSE;

}

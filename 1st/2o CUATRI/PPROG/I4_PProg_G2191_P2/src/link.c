#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "link.h"


/**
* @brief link definition
*
* Struct for storing a link with its
* properties.
*/

struct _Link{
  Id id;  /*!< id (long int) */
  char name[WORD_SIZE +1];  /*!< char string */
  Id link1;  /*!< LEFT LINK (north/west) */
  Id link2;  /*!< RIGHT LINK (south/east) */
  LINK_ST mode;  /*!< link enumeration */
  Id key; /*!< key id */
};


Link *link_create(Id id){
  Link *newLink;

  if (id==NO_ID)
    return NULL;

  newLink=(Link *)malloc(sizeof(Link));
  if (newLink==NULL)
    return NULL;

  newLink->id = id;
  newLink->name[0] = '\0';
  newLink->link1 = NO_ID;
  newLink->link2 = NO_ID;
  newLink->key = 0;
  return newLink;
}


STATUS link_destroy(Link *link){
  if (link==NULL)
    return ERROR;

  free (link);
  link=NULL;
  return OK;
}

STATUS link_set_id (Link *link, Id id){
  if (link==NULL || id==NO_ID)
    return ERROR;

  link->id=id;
  return OK;
}
STATUS link_set_key (Link *link, Id key){
  if (link==NULL || key==NO_ID)
    return ERROR;

  link->key=key;
  return OK;
}


STATUS link_set_name (Link *link, char *name){
  if (link==NULL || name==NULL)
    return ERROR;

  strcpy (link->name, name);
  return OK;
}

STATUS link_set_link1 (Link *link, Id id){
  if (link==NULL || id==NO_ID)
    return ERROR;

  link->link1=id;
  return OK;
}

STATUS link_set_link2 (Link *link, Id id){
  if (link==NULL || id==NO_ID)
    return ERROR;

  link->link2=id;
  return OK;
}

STATUS link_set_status(Link *link, LINK_ST st){
  if (link==NULL || (st!=OPEN && st!=CLOSE))
    return ERROR;

  link->mode=st;
  return OK;
}

Id link_get_id (Link *link){
  if (link==NULL)
    return NO_ID;

  return link->id;
}
Id link_get_key (Link *link){
  if (link==NULL)
    return NO_ID;

  return link->key;
}

Id link_get_link1 (Link *link){
  if (link==NULL)
    return NO_ID;

  return link->link1;
}

Id link_get_link2 (Link *link){
  if (link==NULL)
    return NO_ID;

  return link->link2;
}

const char *link_get_name(Link *link){
  if (link==NULL)
    return NULL;

  return link->name;
}

LINK_ST link_get_status (Link *link){
  if (link==NULL)
    return CLOSE;

  return link->mode;
}

STATUS link_print(Link* link){
  Id idaux = NO_ID;

  if (link==NULL)
    return ERROR;

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", link->id, link->name);

  idaux = link_get_link1 (link);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  idaux = link_get_link2(link);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  return OK;
}

/**
* @brief Contains the function that loads spaces
*
* The file is in charge of loading the structural part of the game such
* as the spaces, the objects and the links.
*
* @file GameManagement.c
* @author Borja Pérez
* @version 3.0
* @date 29-04-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "game.h"
#include "GameManagement.h"
#include "link.h"


/**
* @brief loads the graphics
*
* Detects graphics in a file (P.E graphics.txt) and loads
* them into a game.
*
* @author Borja Pérez
* @param s a pointer to the space where the graphics will be loaded.
* @param filename a string with the name of the file in where the spaces are loaded.
* @param id long int
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/
STATUS game_management_load_graphics(Space * s, char * filename, Id id);

STATUS game_management_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;  /* File where the data is stored */
  char line[WORD_SIZE] = "";  /* Auxiliary string to save each line in the file, to divide it later */
  char name[WORD_SIZE] = "";  /* String to save the space name */
  char* toks = NULL;  /* Auxiliary char to use strtok */
  char sdescription[MAX_DESCRIPTION];
  char ldescription[MAX_DESCRIPTION];
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, up=NO_ID, down=NO_ID;/* Ids to save the neighbour spaces ids and the actual space id */
  Space* space = NULL;  /* Space to be added to the game */
  STATUS status = OK; /* Error declaration */
  int light;
  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {  /* Gets a line from the file, divides it in tokens and saves them in each variable declarated before */
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      toks = strtok(NULL, "|");
      up = atol(toks);
      toks = strtok(NULL, "|");
      down = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(sdescription, toks);
      toks = strtok(NULL, "|");
      strcpy(ldescription, toks);
      toks = strtok(NULL, "|");
      light = atol(toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%s|%s\n", id, name, north, east, south, west, sdescription, ldescription);
#endif
      space = space_create(id); /* Allocates memory and fills the space with the data from the file, then adds the space to the game */
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        space_set_up(space, up);
        space_set_down(space, down);
        space_set_short_description(space, sdescription);
        space_set_long_description(space, ldescription);
        if (light==1)
          space_set_iluminate(space, TRUE);
        else
          space_set_iluminate(space, FALSE);

        game_management_load_graphics(space, "graphics.txt", id);
        game_add_space(game, space);

      }
    }
  }



  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  return status;
}

STATUS game_management_load_objects(Game* game, char* filename){

  FILE* file = NULL;  /* File where the data is stored */
  char line[WORD_SIZE] = "";  /* Auxiliary string to save each line in the file, to divide it later */
  char name[WORD_SIZE] = "";  /* String to save the space name */
  char sdescription[MAX_DESCRIPTION];  /* To store the description of the object (original) */
  char ldescription[MAX_LONG_DESCRIPTION];  /* To store the description of the object (moved) */
  char* toks = NULL;  /* Auxiliary char to use strtok */
  Id id = NO_ID;  /* Id to save the object id */
  Id location = NO_ID;  /* Id to save the object's location */
  STATUS status = OK; /* Error declaration */
  Object * o; /* Object to add to the game */
  int movable, hidden, iluminate, switchedon;
  Id linking=NO_ID;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {  /* Gets a line from the file, divides it in tokens and saves them in each variable declarated before */
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(sdescription, toks);
      toks = strtok(NULL, "|");
      strcpy(ldescription, toks);
      toks = strtok(NULL, "|");
      movable = atol(toks);
      toks = strtok(NULL, "|");
      hidden = atol(toks);
      toks = strtok(NULL, "|");
      linking = atol(toks);
      toks = strtok(NULL, "|");
      iluminate = atol(toks);
      toks = strtok(NULL, "|");
      switchedon = atol(toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%d|%s|%s|%d|%d|%ld|%d|%d", id, name, location, sdescription, ldescription, movable, hidden, linking, iluminate, switchedon);
#endif

      o = object_create(id);  /* Allocates memory and fills the object with the data from the file, then adds the object to the game */
      if (o != NULL) {
        object_set_name(o, name);
        object_set_id(o, id);
        object_set_location(o, location);
        object_set_original_position(o, location);
        object_set_original_description(o, sdescription);
        object_set_moved_description(o, ldescription);
        if (movable==1)
          object_set_prop_Movable(o, TRUE);
        else
          object_set_prop_Movable(o, FALSE);


        if (hidden==1)
          object_set_prop_Hidden(o, TRUE);
        else
          object_set_prop_Hidden(o, FALSE);

        object_set_prop_Open(o, linking);

        if (iluminate==1)
          object_set_prop_Illuminate(o, TRUE);
        else
          object_set_prop_Illuminate(o, FALSE);

        if (switchedon==1)
          object_set_prop_SwitchedOn(o, TRUE);
        else
          object_set_prop_SwitchedOn(o, FALSE);

        game_add_object(game, o);
      }
    }
  }
  fclose(file);
  return status;
}

STATUS game_management_load_links(Game* game, char* filename){

  FILE* file = NULL;  /* File where the data is stored */
  char line[WORD_SIZE] = "";  /* Auxiliary string to save each line in the file, to divide it later */
  char name[WORD_SIZE] = "";  /* String to save the link name */
  char* toks = NULL;  /* Auxiliary char to use strtok */
  Id id = NO_ID;  /* Id to save the link id */
  Id link1 = NO_ID;  /* Id to save the id of link1 */
  Id link2 = NO_ID;  /* Id to save the id of link2 */
  Id aux; /* Auxiliary to check if link is 0 or 1 */
  STATUS status = OK; /* Error declaration */
  Link *l; /* Link to add to the game */
  LINK_ST linking; /* Info about the open or closed link saved here */
  Id key;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {  /* Gets a line from the file, divides it in tokens and saves them in each variable declarated before */
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      link1 = atol(toks);
      toks = strtok(NULL, "|");
      link2 = atol(toks);
      toks = strtok(NULL, "|");
      aux = atol(toks);
      toks = strtok(NULL, "|");
      key = atol(toks);
      if (aux==0)
        linking=OPEN;
      else if (aux==1)
        linking=CLOSE;
      else
        return ERROR;

#ifdef DEBUG
      printf("Leido: %ld|%s", id, name);
#endif

      l = link_create(id);  /* Allocates memory and fills the link with the data from the file, then adds the link to the game */
      if (l != NULL) {
        link_set_name(l, name);
        link_set_id(l, id);
        link_set_link1(l, link1);
        link_set_link2(l, link2);
        link_set_status(l, linking);
        link_set_key(l, key);
      }
      game_add_link(game, l);
    }
  }
  fclose(file);
  return status;
}

STATUS game_management_load_graphics(Space * s, char * filename, Id id){

  FILE * f = NULL;
  int num, i;
  char line[110];

  f = fopen(filename, "r");

  if(!f){ fprintf(stderr, "ERROR"); return ERROR;}

  while(feof(f) == 0){
    fscanf(f ,"%d", &num);

    if(num != id){
        fscanf(f, "%s", line);
    }else{
      for(i=0; i<30; i++){
        fgets(line, 110, f);
        space_set_gdesc_line(s, i, line);

      }
      fclose(f);
      return OK;

    }
  }
  fclose(f);
  return ERROR;
}
STATUS game_management_save_game(Game *game, char * filename){
  FILE * f = NULL;
  int i;

  f = fopen(filename, "w");

  if(!f){ return ERROR;}

  fprintf(f, "#p:%ld\n\n\n", game_get_player_location(game));

  /*Link:ID|STATUS*/

  for(i=0;i<MAX_LINKS;i++){
    if(game_get_link(game, i) != NULL)
      fprintf(f, "#l:%ld|%d\n", link_get_id(game_get_link(game, i)), link_get_status(game_get_link(game, i)));
  }
  fprintf(f,"\n\n\n");

  /*Object:ID|Movable|Moved|Hidden|Open|Iluminate|SwitchedOn*/

  for(i=0;i<50;i++){
    if(get_object_from_game(game, i) != NULL)
      fprintf(f, "#o:%ld|%ld|%d|%d|%d|%ld|%d|%d\n", object_get_id(get_object_from_game(game, i)),game_get_object_location(get_object_from_game(game, i))  ,object_get_prop_Movable(get_object_from_game(game, i)), object_get_prop_Moved(get_object_from_game(game, i)), object_get_prop_Hidden(get_object_from_game(game, i)), object_get_prop_Open(get_object_from_game(game, i)), object_get_prop_Illuminate(get_object_from_game(game, i)), object_get_prop_SwitchedOn(get_object_from_game(game, i)));
  }

  return OK;
}

STATUS game_management_load_game(Game *game, char * filename){

  char line[256];
  char* toks = NULL;
  FILE * f = NULL;
  Id playerId = NO_ID;
  Id linkId = NO_ID;
  int aux;
  Id objId = NO_ID;
  int p1, p2, p3, p4, p5, p6;

  f = fopen(filename, "r");
  if(!f) return ERROR;


  while (fgets(line, WORD_SIZE, f)) {
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      playerId = atol(toks);
      game_set_player_location(game, playerId);

    }
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      linkId = atol(toks);
      toks = strtok(NULL, "|");
      aux = atol(toks);
      link_set_status(game_get_link(game, linkId), aux);
  }
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      objId = atol(toks);
      toks = strtok(NULL, "|");
      aux = atol(toks);
      toks = strtok(NULL, "|");
      p1 = atol(toks);
      toks = strtok(NULL, "|");
      p2 = atol(toks);
      toks = strtok(NULL, "|");
      p3 = atol(toks);
      toks = strtok(NULL, "|");
      p4 = atol(toks);
      toks = strtok(NULL, "|");
      p5 = atol(toks);
      toks = strtok(NULL, "|");
      p6 = atol(toks);
      game_set_object_location(get_object_from_game(game, objId-1), aux);
      object_set_prop_Movable(get_object_from_game(game, objId-1), p1);
      object_set_prop_Moved(get_object_from_game(game, objId-1), p2);
      object_set_prop_Hidden(get_object_from_game(game, objId-1), p3);
      object_set_prop_Open(get_object_from_game(game, objId-1),p4);
      object_set_prop_Illuminate(get_object_from_game(game, objId-1),p5);
      object_set_prop_SwitchedOn(get_object_from_game(game, objId-1),p6);

    }
  }

  return OK;

}

#include <stdio.h>
#include "space.h"
#include "dialogue.h"
#include "player.h"
#include <stdlib.h>
#include <string.h>

char *dialogue_check_space_error(Game *game, Id space){
  char *text;
  if (game==NULL || space==NO_ID)
    return NULL;
  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf (text, "Sorry, you cannot check the description of '%s' space because it is not iluminated yet. Keep working on the game!!. Tip: Find a candle and turn it on!", space_get_short_description(game_get_space(game, space)));
  return text;
}

char *dialogue_check_space_success(Game *game, Id space){
  char *text;
  if (game==NULL || space==NO_ID)
    return NULL;
  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf (text, "Checking description of '%s': ", space_get_short_description(game_get_space(game, space)));
  return text;
}

char *dialogue_check_error(char *oname){
  char *text;
  if (oname==NULL)
    return NULL;
  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf (text, "Sorry, there isn't any object or space in the game with the name '%s'. Keep playing and never give up!!", oname);
  return text;
}

char *dialogue_check_object_success(Object *object){
  char *text;
  if (object==NULL)
    return NULL;
  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  if (object_get_prop_Moved(object)==TRUE){
    sprintf (text, "You are checking the %s, which is not in its original position: %s", object_get_name(object), object_get_moved_description(object));
    return text;
  }
  else{
    sprintf (text, "You are checking the %s, which is in its original position: %s", object_get_name(object), object_get_original_description(object));
    return text;
  }
}

char *dialogue_movement_success(Game *game, Id space, char *cardinal){
  char *text;
  char *long_cardinal;
  if (game==NULL || space==NO_ID || cardinal==NULL)
    return NULL;
  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  long_cardinal=(char *)malloc(MAX_DESCRIPTION*(sizeof(char)));
  if (long_cardinal==NULL){
    free (text);
    return NULL;
  }

  if (strcmp("s", cardinal)==0)
    strcpy(long_cardinal, "south");

  else if (strcmp("n", cardinal)==0)
    strcpy(long_cardinal, "north");

  else if (strcmp("e", cardinal)==0)
    strcpy(long_cardinal, "east");

  else if (strcmp("w", cardinal)==0)
    strcpy(long_cardinal, "west");

  else if (strcmp("u", cardinal)==0)
    strcpy(long_cardinal, "up");

  else if (strcmp("d", cardinal)==0)
    strcpy(long_cardinal, "down");

  else
    strcpy(long_cardinal, cardinal);

  sprintf (text, "You've moved %s. Now you are in %s space", long_cardinal, space_get_short_description(game_get_space(game, space)));
  free (long_cardinal);
  return text;
}

char *dialogue_movement_error(Game *game, Id space, char *cardinal){
  char *text;
  char *long_cardinal;
  if (game==NULL || space==NO_ID || cardinal==NULL)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  long_cardinal=(char *)malloc(MAX_DESCRIPTION*(sizeof(char)));
  if (long_cardinal==NULL){
    free (text);
    return NULL;
  }

  if (strcmp("s", cardinal)==0)
    strcpy(long_cardinal, "south");

  else if (strcmp("n", cardinal)==0)
    strcpy(long_cardinal, "north");

  else if (strcmp("e", cardinal)==0)
    strcpy(long_cardinal, "east");

  else if (strcmp("w", cardinal)==0)
    strcpy(long_cardinal, "west");

  else if (strcmp("u", cardinal)==0)
    strcpy(long_cardinal, "up");

  else if (strcmp("d", cardinal)==0)
    strcpy(long_cardinal, "down");

  else
    strcpy(long_cardinal, cardinal);

  sprintf (text, "You cannot move to %s. You are staying in %s.", long_cardinal, space_get_short_description(game_get_space(game, space)));
  free(long_cardinal);
  return text;
}

char *dialogue_movement_link_error(Game *game, Id space, char *cardinal){
  char *text;
  char *long_cardinal;
  if (game==NULL || space==NO_ID || cardinal==NULL)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  long_cardinal=(char *)malloc(MAX_DESCRIPTION*(sizeof(char)));
  if (long_cardinal==NULL){
    free (text);
    return NULL;
  }

  if (strcmp("s", cardinal)==0)
    strcpy(long_cardinal, "south");

  else if (strcmp("n", cardinal)==0)
    strcpy(long_cardinal, "north");

  else if (strcmp("e", cardinal)==0)
    strcpy(long_cardinal, "east");

  else if (strcmp("w", cardinal)==0)
    strcpy(long_cardinal, "west");

  else if (strcmp("u", cardinal)==0)
    strcpy(long_cardinal, "up");

  else if (strcmp("d", cardinal)==0)
    strcpy(long_cardinal, "down");

  else
    strcpy(long_cardinal, cardinal);

  sprintf (text, "You cannot move to %s because the door is closed. You need to find something to open it!! Keep searching. You are staying in %s.", long_cardinal, space_get_short_description(game_get_space(game, space)));
  free(long_cardinal);
  return text;
}

char *dialogue_throw_die(Die *die){
  char *text;
  if (die==NULL)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf (text, "You have thrown the die!! You have obtained a %d!", die_get_lastroll(die));
  return text;
}

char *dialogue_drop_object_success(Object *object, Game *game, Id act_space){
  char *text;

  if (object==NULL || game==NULL || act_space==NO_ID)
    return NULL;
  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf (text, "You have succesfully dropped the '%s'in the %s space", object_get_name(object), space_get_short_description(game_get_space(game, act_space)));
  return text;
}

char *dialogue_drop_object_error(char *oname, Game *game, Id act_space, int j){
  char *text;

  if (oname==NULL || game==NULL || act_space==NO_ID)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  if (j==0){
    sprintf (text, "You were unable to drop '%s' in '%s' space because that object doesn't exist!!", oname, space_get_short_description(game_get_space(game, act_space)));
    return text;
  }

  if (j==1){
    sprintf (text, "You were unable to drop '%s' in '%s' space because you don't have that object in your inventory!!", oname, space_get_short_description(game_get_space(game, act_space)));
    return text;
  }
  return NULL;
}

char *dialogue_unknown(){
  char *text;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf (text, "You have introduced an unknown command, are you sure you know how to play?? ;)");
  return text;
}


char *dialogue_grasp_object_success(Object *object, Game *game, Id act_space){
  char *text;

  if (object==NULL || game==NULL || act_space==NO_ID)
    return NULL;
  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf (text, "You have succesfully grabbed the '%s' from the %s space", object_get_name(object), space_get_short_description(game_get_space(game, act_space)));
  return text;
}

char *dialogue_grasp_object_error(char *oname, Game *game, Id act_space, int j){
  char *text;

  if (oname==NULL || game==NULL || act_space==NO_ID)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;


  if (j==0){
    if (player_inventory_is_full(get_player_from_game(game))){
      sprintf (text, "You were unable to grasp '%s' from '%s' space because that object doesn't exist!! Apart from that, your inventory is full, so you wouldn't have been able to do that!! Try dropping an object before picking a new one!", oname, space_get_short_description(game_get_space(game, act_space)));
      return text;
    }
    sprintf (text, "You were unable to grasp '%s' from '%s' space because that object doesn't exist!!", oname, space_get_short_description(game_get_space(game, act_space)));
    return text;
  }

  if (player_inventory_is_full(get_player_from_game(game))){
    sprintf (text, "Your inventory is full, so you cannot pick %s from %s!! Try dropping an object before picking a new one!", oname, space_get_short_description(game_get_space(game, act_space)));
    return text;
  }

  if (j==1){
    sprintf (text, "You were unable to grasp '%s' because it is not in your space!! Tip: Check object locations", oname);
    return text;
  }

  return NULL;
}

char *dialogue_grasp_object_error_movable(char *oname, Game *game, Id space_id){
  char *text;
  if (oname == NULL || game==NULL || space_id==NO_ID)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf(text, "You cannot grasp object '%s' from %s because the object is not movable, better luck next time!!", oname, space_get_short_description(game_get_space(game, space_id)));
  return text;
}

char *dialogue_turnon_object_success(char *oname){
  char *text;
  if (oname == NULL)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf(text, "You have succesfully turned on the object '%s'", oname);
  return text;
}

char *dialogue_turnon_object_error(char *oname, int j, int k){
  char *text;
  if (oname == NULL)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  if (k==1){
    sprintf(text, "Before turning on the '%s' you need to grab it!", oname);
    return text;
  }

  if (j==0){
    sprintf(text, "There isn't any object with the name of '%s', try with another name!", oname);
    return text;
  }

  sprintf(text, "Sorry, but the object '%s' cannot be illuminated, keep trying.", oname);
  return text;
}

char *dialogue_turnoff_object_success(char *oname){
  char *text;
  if (oname == NULL)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf(text, "You have succesfully turned off the object '%s'", oname);
  return text;
}

char *dialogue_turnoff_object_error(char *oname, int j){
  char *text;
  if (oname == NULL)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  if (j==0){
    sprintf(text, "There isn't any object with the name of '%s', try with another name!", oname);
    return text;
  }

  sprintf(text, "Sorry, but the object '%s' cannot be illuminated, keep trying.", oname);
  return text;
}

char *dialogue_unlock_error(char *link, char *object, int j, int k){
  char *text;
  if (object == NULL || link==NULL)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  if (j==1){
    sprintf(text, "You need to grab first %s in order to open %s", object, link);
    return text;
  }
  if (k==1){
    sprintf(text, "Object %s is not used to open %s", object, link);
    return text;
  }
  sprintf(text, "You sure the object %s or link %s exists?", object, link);
  return text;
}

char *dialogue_unlock_success(char *link, char *object){
  char *text;
  if (object == NULL || link==NULL)
    return NULL;

  text=(char *)malloc(MAX_LONG_DESCRIPTION*(sizeof(char)));
  if (text==NULL)
    return NULL;

  sprintf(text, "Succesfully opened %s with %s", link, object);
  return text;
}

/**
* @brief Defines the game module
*
* It implements the game interface and all
* the associated callbacks for each command.
*
* @file game.c
* @author Juan Moreno
* @version 2.4
* @date 07-04-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "game.h"
#include "GameManagement.h"
#include "dialogue.h"

#define N_CALLBACK 12  /*!< Number of callback functions */

/**
* @brief game definition
*
* Struct for storing the elements of the game.
*/

struct _Game{
  Player * player;  /*!< Information about the player/s */
  Object * object[MAX_OBJ];  /*!< Information about the object/s */
  Space* spaces[MAX_SPACES + 1];  /*!< Information about the spaces defined in the board */
  T_Command last_cmd;  /*!< Saves the last command typed */
  Die * die;  /*!< Contains a die */
  STATUS last_command_status;  /*!< Saves the last command typed's result */
  char aux[WORD_SIZE];  /*!< character for writing */
  Link * links[MAX_LINKS];  /*!< link variable */
};


/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game
*/
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_grasp(Game* game);
void game_callback_drop(Game* game);
void game_callback_throw(Game* game);
void game_callback_check(Game* game);
void game_callback_move(Game* game);
void game_callback_turnon(Game* game);
void game_callback_turnoff(Game* game);
void game_callback_unlock(Game* game);
void game_callback_save(Game* game);
void game_callback_load(Game* game);


static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_grasp,
  game_callback_drop,
  game_callback_throw,
  game_callback_check,
  game_callback_move,
  game_callback_turnon,
  game_callback_turnoff,
  game_callback_unlock,
  game_callback_save,
  game_callback_load};

/**
   Private functions
*/

/**
* @brief adds a space
*
* Function that implements spaces by
* using the set module to add values.
*
* @author Juan Moreno
* @param game pointer to game.
* @param space pointer to space.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_add_space(Game* game, Space* space);

/**
* @brief gets and id
*
* Function in charge of returning
* the id of a space in the game.
*
* @author Juan Moreno
* @param game pointer to game.
* @param position int.
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id game_get_space_id_at(Game* game, int position);

/**
* @brief sets location
*
* Function in charge of setting a location
* for a player in the game.
*
* @author Juan Moreno
* @param game pointer to game.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_set_player_location(Game* game, Id id);


/**
   Game interface implementation
*/

Game *game_create() {
  int i;
  Game *game;

  game=(Game *)malloc(sizeof(Game));
  if (game==NULL)
    return NULL;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }
  game->player = player_create(NO_ID);

  for(i=0; i<MAX_OBJ; i++){

    game->object[i] = NULL;
  }
  for (i = 0; i < MAX_LINKS; i++) {
    game->links[i] = NULL;
  }

  game->die = die_create(NO_ID);

  game->last_command_status = OK;

  game->last_cmd = NO_CMD;

  strcpy(game->aux, "NOTHING");
  return game;
}

STATUS game_create_from_file(Game* game, char* filename) {

  if (game== NULL || filename==NULL)
    return ERROR;

  if (game_management_load_spaces(game, filename) == ERROR)
    return ERROR;

  if (game_management_load_objects(game, filename) == ERROR)
    return ERROR;
  if (game_management_load_links(game, filename) == ERROR)
    return ERROR;
  game_set_player_location(game, game_get_space_id_at(game, 0));



  return OK;
}

STATUS game_destroy(Game* game) {
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }

  for(i=0; i<MAX_OBJ; i++){
    object_destroy(game->object[i]);
  }
  for(i=0; i<MAX_LINKS; i++){
    link_destroy(game->links[i]);
  }
  player_destroy(game->player);
  die_destroy(game->die);
  free (game);
  return OK;
}

STATUS game_add_space(Game* game, Space* space) {
  int i = 0;

  if (space == NULL) {
    return ERROR;
  }

  while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
    i++;
  }

  if (i >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}



STATUS game_add_object(Game* game, Object* object) {
  int i = 0;

  if (object == NULL) {
    return ERROR;
  }

  while ( (i < MAX_OBJ) && (game->object[i] != NULL)){
    i++;
  }

  if (i >= MAX_OBJ){
    return ERROR;
  }

  game->object[i] = object;

  return OK;
}

Id game_get_space_id_at(Game* game, int position) {

  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }

  return NULL;
}

STATUS game_set_player_location(Game* game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }

  player_set_id(game->player, id);
  return OK;
}


STATUS game_set_object_location(Object* object, Id id) {


  if (id == NO_ID) {
    return ERROR;
  }

  object_set_location(object, id);

  return OK;
}


Id game_get_player_location(Game* game) {
  return player_get_id(game->player);
}

Id game_get_object_location(Object* object) {
  return object_get_location(object);
}
int game_get_die_lastroll(Game * game){

  return die_get_lastroll(game->die);
}


STATUS game_update(Game* game, T_Command cmd) {
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

T_Command game_get_last_command(Game* game){
  return game->last_cmd;
}

STATUS game_get_last_command_status(Game* game){
  return game->last_command_status;
}

void game_print_data(Game* game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }
  for (i=0; i<MAX_OBJ; i++){
    printf("=> Object location: %d\n", (int) object_get_location(game->object[i]));
  }
  printf("=> Player location: %d\n", (int) player_get_id(game->player));
  printf("prompt:> ");
}

BOOL game_is_over(Game* game) {
  return FALSE;
}

/**
   Callbacks implementation for each action
*/

/**
* @brief creates the "unknown" command
*
* when you write a command that not exists,
* unknown is written.
*
* @author Juan Moreno
* @return void function.
*/

void game_callback_unknown(Game* game) {
  char *message;
  message=dialogue_unknown();
  strcpy(game->aux, message);
  free (message);
}

/**
* @brief creates the "exit" command
*
* Exits the game when command is selected.
*
* @author Juan Moreno
* @return void function.
*/

void game_callback_exit(Game* game) {
  printf ("Exiting the game... Thanks for playing and hope to see you soon!!\n");
}

/**
* @brief creates the "grasp" command
*
* First asks for an object name in the graphic engine's command terminal,
* then if the player is already holding an object, the object requested doesnt exist
* in that space or the space hasnt loaded correctly ends. If not, moves the object
* to a special space recorded as player inventory (-7), copies the object in the
* player object and deletes the object from the set in the space.
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/

void game_callback_grasp(Game* game){

  char oname[16];
  int i, j=0;
  Id space_id = NO_ID;
  char *message;

  scanf("%s",oname);
  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    game->last_command_status = ERROR;
    return;
  }

  if ( oname == NULL){
    game->last_command_status = ERROR;
    return;
  }

  /*CHECKING IF THERE IS AN OBJECT WITH THE NAME INTRODUCED*/
  for(i=0;i<MAX_OBJ;i++){
    if(strcmp(oname, object_get_name(game->object[i])) == 0){
      j=1;
      i=i+MAX_OBJ;
    }
  }

  if (player_inventory_is_full(game->player)==TRUE){
    message=dialogue_grasp_object_error(oname, game, space_id, j);
    strcpy(game->aux, message);
    free (message);
    game->last_command_status = ERROR;
    return;
  }


  for (i=0; i<MAX_OBJ; i++){
    if(strcmp(object_get_name(game->object[i]), oname) == 0){
      if(game_get_object_location(game->object[i]) != space_id){
        message=dialogue_grasp_object_error(oname, game, space_id, j);
        strcpy(game->aux, message);
        free (message);
        game->last_command_status = ERROR;
        return;
      }
      if (object_get_prop_Movable(game->object[i])==TRUE){
        player_set_object(game->player, object_get_id(game->object[i]));
        game_set_object_location(game->object[i], -7);
        message=dialogue_grasp_object_success(game->object[i], game, space_id);
        strcpy(game->aux, message);
        free (message);
        game->last_command_status = OK;
        return;
      }
      message=dialogue_grasp_object_error_movable(oname, game, space_id);
      strcpy(game->aux, message);
      free (message);
      game->last_command_status = ERROR;
      return;
     }
  }
  message=dialogue_grasp_object_error(oname, game, space_id, j);
  strcpy(game->aux, message);
  free (message);
  game->last_command_status = ERROR;
}

/**
* @brief creates the "drop" command
*
* If the player is not holding any objects, or the space hasnt
* loaded correctly ends the execution, if not reactivates the object in game
* adds the object to the space set and deletes the player's object
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/

void game_callback_drop(Game* game){
  char *message;
  char oname[16];
  Id space_id = NO_ID;
  int i, j=0;

  scanf("%s",oname);
  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    game->last_command_status = ERROR;
    return;
  }

  /*CHECKING IF THERE IS AN OBJECT WITH THE NAME INTRODUCED*/
  for(i=0;i<MAX_OBJ;i++){
    if(strcmp(oname, object_get_name(game->object[i])) == 0){
      j=1;
      i=i+MAX_OBJ;
    }
  }

  if(player_inventory_is_empty(game->player)==TRUE){
    message=dialogue_drop_object_error(oname, game, space_id, j);
    strcpy(game->aux, message);
    free (message);
    game->last_command_status = ERROR;
    return;
  }

  for(i=0;i<MAX_OBJ;i++){
    if(game_get_object_location(game->object[i])==-7){
      if(strcmp(oname, object_get_name(game->object[i])) == 0){
        game_set_object_location(game->object[i], space_id);
        player_remove_object(game->player, object_get_id(game->object[i]));
        message=dialogue_drop_object_success(game->object[i], game, space_id);
        strcpy(game->aux, message);
        free (message);
        game->last_command_status = OK;
        return;
      }
    }
  }

  message=dialogue_drop_object_error(oname, game, space_id, j);
  strcpy(game->aux, message);
  free (message);
  game->last_command_status = ERROR;
}

/**
* @brief creates the "throw" command
*
* Rolls the die contained in the game structure,
* saving its value within it.
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/

void game_callback_throw(Game* game){
  char *message;

  srand(time(NULL));
  die_roll(game->die);
  message=dialogue_throw_die(game->die);
  strcpy(game->aux, message);
  free(message);
  game->last_command_status = OK;
}

/**
* @brief description of elements.
*
* When checking a principal element of the
* game, it shows a description of the element
* you choose.
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/

void game_callback_check(Game* game){
  char *message;
  char oname[16];
  int i;
  Id space_id = NO_ID;

  scanf("%s",oname);
  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    game->last_command_status = ERROR;
    return;
  }

  if ( oname == NULL){
    game->last_command_status = ERROR;
    return;
  }


  if(strcasecmp(oname, "space")==0){
    for (i=0; i<MAX_OBJ; i++){/*Comprobamos si hay algun objeto encendido, en cuyo caso si mostramos descripcion*/
      if (object_get_location(get_object_from_game(game, i))==-7){
        if (object_get_prop_SwitchedOn(get_object_from_game(game, i))==TRUE){
          message=dialogue_check_space_success(game, space_id);
          strcpy(game->aux, message);
          strcpy(game->aux, space_get_long_description(game_get_space(game, space_id)));
          free(message);
          game->last_command_status = OK;
          return;
        }
      }
    }

    if (space_get_iluminate(game_get_space(game, space_id))==FALSE){
      message=dialogue_check_space_error(game, space_id);
      strcpy(game->aux, message);
      free (message);
      game->last_command_status = ERROR;
      return;
    }
    else{
      message=dialogue_check_space_success(game, space_id);
      strcpy(game->aux, message);
      strcpy(game->aux, space_get_long_description(game_get_space(game, space_id)));
      free(message);
      game->last_command_status = OK;
      return;
    }
  }


  for (i=0; i<MAX_OBJ; i++){
    if(strcasecmp(object_get_name(game->object[i]), oname) == 0){

      if (object_get_location(game->object[i])==object_get_original_position(game->object[i]))
        object_set_prop_Moved(game->object[i], FALSE);
      else
        object_set_prop_Moved(game->object[i], TRUE);

      if (object_get_prop_Moved(game->object[i])==FALSE){
        message=dialogue_check_object_success(game->object[i]);
        strcpy(game->aux, message);
        free (message);
        game->last_command_status = OK;
        return;
      }
      else{
        message=dialogue_check_object_success(game->object[i]);
        strcpy(game->aux, message);
        free (message);
        game->last_command_status = OK;
        return;
     }
   }
  }
  message=dialogue_check_error(oname);
  strcpy(game->aux, message);
  free (message);
  game->last_command_status = ERROR;
}

/**
* @brief command that moves an object
*
* It is the function in charge of linking
* the commands "following" and "previous".
*
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/

void game_callback_move(Game* game){

  char cardinal[16];
  int i;
  Id space_id = NO_ID;
  char *message;
  scanf("%s",cardinal);
  space_id = game_get_player_location(game);



  if(strcmp(cardinal, "north") == 0 || strcmp(cardinal, "n") == 0){
    for(i=0; i<5; i++){
      if (link_get_link2(game->links[i]) == space_id){
        if (link_get_status(game->links[i])==OPEN){
          game_set_player_location(game, link_get_link1(game->links[i]));
          message=dialogue_movement_success(game, link_get_link1(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
        if (link_get_status(game->links[i])==CLOSE){
          message=dialogue_movement_link_error(game, link_get_link1(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
      }
    }
  }

  if(strcmp(cardinal, "south") == 0 || strcmp(cardinal, "s") == 0){
    for(i=0; i<5; i++){
      if (link_get_link1(game->links[i]) == space_id){
        if (link_get_status(game->links[i])==OPEN){
          game_set_player_location(game, link_get_link2(game->links[i]));
          message=dialogue_movement_success(game, link_get_link2(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
        if (link_get_status(game->links[i])==CLOSE){
          message=dialogue_movement_link_error(game, link_get_link1(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
      }
    }
  }
  if(strcmp(cardinal, "east") == 0 || strcmp(cardinal, "e") == 0){
    for(i=5; i<10; i++){
      if (link_get_link1(game->links[i]) == space_id){
        if (link_get_status(game->links[i])==OPEN){
          game_set_player_location(game, link_get_link2(game->links[i]));
          message=dialogue_movement_success(game, link_get_link2(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
        if (link_get_status(game->links[i])==CLOSE){
          message=dialogue_movement_link_error(game, link_get_link1(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
      }
    }
  }

  if(strcmp(cardinal, "west") == 0 || strcmp(cardinal, "w") == 0){
    for(i=5; i<10; i++){
      if (link_get_link2(game->links[i]) == space_id ){
        if (link_get_status(game->links[i])==OPEN){
          game_set_player_location(game, link_get_link1(game->links[i]));
          message=dialogue_movement_success(game, link_get_link1(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
        if (link_get_status(game->links[i])==CLOSE){
          message=dialogue_movement_link_error(game, link_get_link1(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
      }
    }
  }

   if(strcmp(cardinal, "up") == 0 || strcmp(cardinal, "u") == 0){
    for(i=9; i<MAX_LINKS; i++){
      if (link_get_link1(game->links[i]) == space_id ){
        if (link_get_status(game->links[i])==OPEN){
          game_set_player_location(game, link_get_link2(game->links[i]));
          message=dialogue_movement_success(game, link_get_link2(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
        if (link_get_status(game->links[i])==CLOSE){
          message=dialogue_movement_link_error(game, link_get_link1(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
      }
    }
  }

  if(strcmp(cardinal, "down") == 0 || strcmp(cardinal, "d") == 0){
    for(i=9; i<MAX_LINKS; i++){
      if (link_get_link2(game->links[i]) == space_id ){
        if (link_get_status(game->links[i])==OPEN){
          game_set_player_location(game, link_get_link1(game->links[i]));
          message=dialogue_movement_success(game, link_get_link1(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
        if (link_get_status(game->links[i])==CLOSE){
          message=dialogue_movement_link_error(game, link_get_link1(game->links[i]), cardinal);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
      }
    }
  }

  message=dialogue_movement_error(game, space_id, cardinal);
  strcpy(game->aux, message);
  free (message);
  game->last_command_status = ERROR;


}

/**
* @brief creates de "turn on command".
*
* It creates the command that enables us to turn on
* objects or spaces that have that property.
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/

void game_callback_turnon(Game* game){
  char oname[16];
  int i, j=0, k=0; /*k used to know is the error is because object is not in the inventory*/
  char *message;

  if (game==NULL)
    return;

  scanf("%s",oname);

  if (oname == NULL){
    game->last_command_status = ERROR;
    return;
  }

  /*CHECKING IF THERE IS AN OBJECT WITH THE NAME INTRODUCED*/
  for(i=0;i<MAX_OBJ;i++){
    if(strcmp(oname, object_get_name(game->object[i])) == 0){
      j=1;
      i=i+MAX_OBJ;
    }
  }

  for (i=0; i<MAX_OBJ; i++){
    if(strcmp(object_get_name(game->object[i]), oname) == 0){
      if(game_get_object_location(game->object[i])!=-7)
        k=1;
      else
        if (object_get_prop_Illuminate(game->object[i])==TRUE){
          object_set_prop_SwitchedOn(game->object[i], TRUE);
          message=dialogue_turnon_object_success(oname);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
      }
    }
  message=dialogue_turnon_object_error(oname, j, k);
  strcpy(game->aux, message);
  free(message);
  game->last_command_status = ERROR;
}

/**
* @brief creates de "turn off command".
*
* It creates the command that enables us to turn off
* objects or spaces that have that property.
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/

void game_callback_turnoff(Game* game){
  char oname[16];
  int i, j=0;
  char *message;

  if (game==NULL)
    return;

  scanf("%s",oname);

  if (oname == NULL){
    game->last_command_status = ERROR;
    return;
  }

  /*CHECKING IF THERE IS AN OBJECT WITH THE NAME INTRODUCED*/
  for(i=0;i<MAX_OBJ;i++){
    if(strcmp(oname, object_get_name(game->object[i])) == 0){
      j=1;
      i=i+MAX_OBJ;
    }
  }

  for (i=0; i<MAX_OBJ; i++){
    if(strcmp(object_get_name(game->object[i]), oname) == 0){
      if (object_get_prop_Illuminate(game->object[i])==TRUE){
        object_set_prop_SwitchedOn(game->object[i], FALSE);
        message=dialogue_turnoff_object_success(oname);
        strcpy(game->aux, message);
        free(message);
        game->last_command_status = OK;
        return;
      }
    }
  }
  message=dialogue_turnoff_object_error(oname, j);
  strcpy(game->aux, message);
  free(message);
  game->last_command_status = ERROR;
}



/* --------------------------------------------------------------------
NEW FUNCTIONS
---------------------------------------------------------------------- */
Object *get_object_from_game(Game *game, int i){
  if (game==NULL || i<-1 || i>MAX_OBJ)
    return NULL;

  return game->object[i];
}

Player *get_player_from_game(Game *game){
  if (game==NULL)
    return NULL;

  return game->player;
}

char * game_get_aux(Game *game){

 return game->aux;
}

STATUS game_add_link(Game* game, Link* link) {
  int i = 0;

  if (link == NULL) {
    return ERROR;
  }

  while ( (i < MAX_LINKS) && (game->links[i] != NULL)){
    i++;
  }

  if (i >= MAX_LINKS) {
    return ERROR;
  }

  game->links[i] = link;

  return OK;
}
Link * game_get_link(Game *game, Id id){

  return game->links[id];
}

/**
* @brief creates de "unlock" command.
*
* It creates the command that enables us to open links
* with objecs that have that kind of property
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/


void game_callback_unlock(Game* game){

  char command[64];
  char link[30], object[30];
  int i,j=0, count = 0;
  Id obj = NO_ID;
  char *message;
  int w=0;
  int k=0;

  gets(command);

  for(i=1; i<64;i++){
      if(command[i]==32){ count = i; break;}
      link[j] = command[i];
      j++;

  }

  j = 0;
  for(i=count+6; i<64 ;i++){
      object[j] = command[i];
      j++;

  }
      fprintf(stdout, "%s %s", link,object);

  for (i=0; i<MAX_OBJ; i++){
    if(strcasecmp(object_get_name(game->object[i]), object) == 0){
      obj = object_get_id(game->object[i]);
      if(game_get_object_location(game->object[i]) != -7){
        w=1;
        message=dialogue_unlock_error(object, link, w, k);
        strcpy(game->aux, message);
        free(message);
        game->last_command_status = ERROR;
        return;
      }
    }
  }

  if(obj == NO_ID){
    message=dialogue_unlock_error(link, object, w, k);
    strcpy(game->aux, message);
    free(message);
    game->last_command_status = ERROR;
    return;
  }

  for(i=0; i<10;i++){
    if(strcmp(link_get_name(game_get_link(game, i)), link) == 0){
      k=1;
      if(link_get_key(game_get_link(game, i)) == obj){
        if(link_get_status(game_get_link(game, i)) == CLOSE){
          link_set_status(game_get_link(game, i), OPEN);
          message=dialogue_unlock_success(link, object);
          strcpy(game->aux, message);
          free(message);
          game->last_command_status = OK;
          return;
        }
      }
    }
  }
  message=dialogue_unlock_error(link, object, w, k);
  strcpy(game->aux, message);
  free(message);
  game->last_command_status = ERROR;

}





/**
* @brief creates de "save" command.
*
* It creates the command that enables us to save
* the game and creates a new file with the saved game.
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/


void game_callback_save(Game* game){
  char filename[32];
  scanf("%s", filename);
  game->last_command_status =game_management_save_game(game, filename);
}

/**
* @brief creates de "load" command.
*
* It creates the command that enables us to load games
* that have already been saved.
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/

void game_callback_load(Game* game){
  char filename[32];
  scanf("%s", filename);
  game->last_command_status = game_management_load_game(game, filename);
}

Die *get_die_from_game(Game *game){
  if (game==NULL)
    return NULL;

  return game->die;
}

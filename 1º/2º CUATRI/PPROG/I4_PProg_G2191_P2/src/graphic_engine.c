/**
* @brief defines the graphic engine
*
* Module that contains the graphic information
* of the game, it is in charge of printing everything.
*
* @file graphic_engine.c
* @author Dan Roife
* @version 1.2
* @date 07-04-2018
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "screen.h"
#include "graphic_engine.h"
#include "game.h"

#define SSIZE 11  /*!< maximum size */

/**
* @brief graphic design
*
* Struct that include the variables that will
* help us show the design of our game.
*/

struct _Graphic_engine{
  Area *map;  /*!< pointer to area (map) */
  Area *descript;  /*!< pointer to area (description) */
  Area *banner;  /*!< pointer to area (banner) */
  Area *help;  /*!< pointer to area (help) */
  Area *feedback;  /*!< pointer to area (feedback) */
};


Graphic_engine *graphic_engine_create(){
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;

  screen_init();
  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));

  ge->map      = screen_area_init( 1, 1, 110, 30);
  ge->descript = screen_area_init(112, 1, 29, 24);
  ge->banner   = screen_area_init( 1, 32, 110, 4);
  ge->help     = screen_area_init( 112, 26, 29, 05);
  ge->feedback = screen_area_init( 112,32, 29, 4);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge){
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game){
  int i;
  Id obj_loc = NO_ID, player_loc = NO_ID;
  Space* space_act = NULL;
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[];


  player_loc = game_get_player_location(game);

  /* Paint the in the map area */

  screen_area_clear(ge->map);

  space_act = game_get_space(game, player_loc);


  /*In room 7, if last roll was a 5 you will be able to grasp the key*/
  if (die_get_lastroll(get_die_from_game(game))==5){
    object_set_prop_Movable(get_object_from_game(game, 14), TRUE);
  }


  /*If you are in Mafias room, every object will be thrown to the floor*/
  if (player_loc==8){
    for (i=0; i<MAX_OBJ; i++){
      if (game_get_object_location(get_object_from_game(game, i))==-7){
        game_set_object_location(get_object_from_game(game, i), 7);
        player_remove_object(get_player_from_game(game), object_get_id(get_object_from_game(game, i)));
      }
    }
      
    player_set_object(get_player_from_game(game), 4);
    game_set_object_location(get_object_from_game(game, 4), -7);
    player_set_object(get_player_from_game(game), 19);
    game_set_object_location(get_object_from_game(game, 4), -7);
  }


  /*Bucle para comprobar si tenemos algun objeto que este encendido, en cuyo caso tambien imprimimos la sala*/
  if(space_get_iluminate(space_act) == TRUE){
    for(i=0; i<30;i++){
      sprintf(str, "%s", space_get_gdesc_line(space_act, i));
      screen_area_puts(ge->map, str);
    }
  }
  else{
    for (i=0; i<MAX_OBJ; i++){
      if (object_get_location(get_object_from_game(game, i))==-7){
        if (object_get_prop_SwitchedOn(get_object_from_game(game, i))==TRUE){
          for(i=0; i<30;i++){
            sprintf(str, "%s", space_get_gdesc_line(space_act, i));
            screen_area_puts(ge->map, str);
          }
        }
      }
    }
  }

  /* Paint the in the description area */
  screen_area_clear(ge->descript);
  screen_area_puts(ge->descript, space_get_short_description(game_get_space(game, player_loc)));
  for(i=0; i<MAX_OBJ; i++){
    if ((obj_loc = game_get_object_location(get_object_from_game(game, i))) != NO_ID){
      if(obj_loc == -7){
        sprintf(str, " (%d) Obj %s:%s",i+1, object_get_name(get_object_from_game(game, i)), " Player Inv" );
        screen_area_puts(ge->descript, str);
      }
      else{
        if (object_get_prop_Hidden(get_object_from_game(game, i))==TRUE){
          sprintf(str, " (%d) Obj %s: Hidden",i+1, object_get_name(get_object_from_game(game, i)));
          screen_area_puts(ge->descript, str);
        }
        else{
          sprintf(str, " (%d) Obj %s: Room %d",i+1, object_get_name(get_object_from_game(game, i)), (int)object_get_location(get_object_from_game(game, i)));
          screen_area_puts(ge->descript, str);
        }
      }
    }
  }
  sprintf(str, " Last Die Roll:%d", game_get_die_lastroll(game));
  screen_area_puts(ge->descript, str);
  /* Paint the in the banner area */
  screen_area_puts(ge->banner, " The game of the Goose ");

  /* Paint the in the help area */
  screen_area_clear(ge->help);
  sprintf(str, "The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "move, check, throw, grasp, drop, exit, turn on, turn off, save, load, unlock");
  screen_area_puts(ge->help, str);

  /* Paint the status in the feedback area */
  last_cmd = game_get_last_command(game);
  if(game_get_last_command_status(game) == ERROR)
    sprintf(str, " %s: ERROR", cmd_to_str[last_cmd-NO_CMD]);
  else
    sprintf(str, " %s: %s", cmd_to_str[last_cmd-NO_CMD], "OK");
  screen_area_puts(ge->feedback, str);

  /*printing the long description*/
  screen_area_clear(ge->banner);
  sprintf(str, " %s", game_get_aux(game));
  screen_area_puts(ge->banner, str);

  /* Dump to the terminal */
  screen_paint();
  printf("prompt:> ");
}

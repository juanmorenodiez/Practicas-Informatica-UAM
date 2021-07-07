/**
* @brief initializes the game
*
* It defines the game loop and contains the MAIN
* function for all the program
*
* @file game_loop.c
* @author Juan Moreno
* @version 3.0
* @date 07-04-2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphic_engine.h"
#include "game.h"

/**
* @brief main function of game
*
* This function is in charge of loading the main
* function of the game, it has everything working in 
* order to do it properly.
*
* @author Juan Moreno
* @param argc int.
* @param argv int.
* @return int value.
*/

int main(int argc, char *argv[]){

  Game *game;
  T_Command command = NO_CMD;
  Graphic_engine *gengine;
  FILE * log = NULL;
  extern char *cmd_to_str[];

  if(argv[2]){
    if(strcmp(argv[2], "-l")==0){

      if(argv[3]==NULL) {    fprintf(stderr, "Error while initializing game.\n"); return 1;}
      log = fopen(argv[3], "w");
    }
  }
  if (argc < 2){
		fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
  return 1;
  }

  game=game_create();
  if (game==NULL)
    return 1;

  if (game_create_from_file(game, argv[1]) == ERROR){
    fprintf(stderr, "Error while initializing game.\n");
    game_destroy(game);
    return 1;
  }
  if ((gengine = graphic_engine_create()) == NULL){
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
    }
  while ( (command != EXIT) && !game_is_over(game) ){
    graphic_engine_paint_game(gengine, game);
    command = command_get_user_input();
    game_update(game, command);
    if(argv[2]){
      if(strcmp(argv[2], "-l")==0){
        if(game_get_last_command_status(game) == ERROR)
          fprintf(log, " %s: %s\n", cmd_to_str[command-NO_CMD], "ERROR");
        else
          fprintf(log, " %s: %s\n", cmd_to_str[command-NO_CMD], "OK");
      }
    }
  }
  if(argv[2])
   if(strcmp(argv[2], "-l")==0) fclose(log);
  graphic_engine_destroy(gengine);
  game_destroy(game);
  return 0;
}

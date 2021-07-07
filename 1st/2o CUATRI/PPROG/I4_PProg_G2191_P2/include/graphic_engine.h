/**
* @brief defines the graphic engine
*
* @file graphic_engine.h
* @author Dan Roife
* @version 2.0
* @date 07-04-2018
*/

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

/**
* @brief graphic design
*
* Struct that include the variables that will
* help us show the design of our game.
*/

typedef struct _Graphic_engine Graphic_engine;

/**
* @brief creates the graphic engine
*
* Allocates the memory for a new graphic
* engine and declares its parts
*
* @author Dan Roife
* @return pointer to a graphic engine.
*/

Graphic_engine* graphic_engine_create();

/**
* @brief frees memory
*
* Frees the memory allocated for the graphic
* engine and its parts.
*
* @author Dan Roife
* @param ge pointer to graphic engine.
* @return void function.
*/

void graphic_engine_destroy(Graphic_engine *ge);

/**
* @brief paints the game
*
* Shows a graphic interface with the
* contents of the game.
*
* @author Dan Roife
* @param ge pointer to graphic engine.
* @param game pointer to game.
* @return void function.
*/

void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

/**
* @brief writes the commands
*
* Enables us to write the command that we want
* to use in a certain moment.
*
* @author Dan Roife
* @param ge pointer to graphic engine.
* @param str string.
* @return void function.
*/

void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif

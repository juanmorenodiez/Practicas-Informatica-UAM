/**
* @brief Contains the declaration for game_reader.c functions
*
* @file GameManagement.h
* @author Borja Pérez
* @version 2.0
* @date 29-04-2018
*/

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
* @brief loads the spaces
*
* Detects spaces in a file (P.E. data.dat) and loads
* them into a game.
*
* @author Borja Pérez
* @param game a pointer to the game where the spaces will be loaded.
* @param filename a string with the name of the file in where the spaces are saved.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_management_load_spaces(Game* game, char* filename);

/**
* @brief loads the objects
*
* Detects objects in a file (P.E. data.dat) and
* loads them into a game
*
* @author Borja Pérez
* @param game a pointer to the game where the objects will be loaded.
* @param filename a string with the name of the file in where the objects are saved.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_management_load_objects(Game* game, char* filename);

/**
* @brief loads the links
*
* Detects links in a file (P.E. data.dat) and
* loads them into a game
*
* @author Borja Pérez
* @param game a pointer to the game where the links will be loaded.
* @param filename a string with the name of the file in where the links are saved.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_management_load_links(Game* game, char* filename);

/**
* @brief saves the game
*
* Function used to save the currect game positioning of objects,
* spaces, etc. and creates a new file
*
* @author Borja Pérez
* @param game a pointer to the game.
* @param filename a string with the name of the file in where the game is saved.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/
STATUS game_management_save_game(Game *game, char * filename);

/**
* @brief saves the game
*
* Function used to load the currect game positioning of objects, 
* spaces, etc. and loads a new file
*
* @author Borja Pérez
* @param game a pointer to the game.
* @param filename a string with the name of the file from where the game is load.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/
STATUS game_management_load_game(Game *game, char * filename);
#endif

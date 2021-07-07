/**
* @brief  It implements the GAME structure declarates
* all public game.c functions
*
* @file game.h
* @author Juan Moreno
* @version 2.1
* @date 07-04-2018
*/

#ifndef GAME_H
#define GAME_H


#include "command.h"
#include "space.h"
#include "object.h"
#include "player.h"
#include "die.h"
#include "link.h"

#define MAX_OBJ 20  /*!< Maximum number of objects */
#define MAX_LINKS 64  /*!< Maximum number of links */

/** The game structure has everything our game needs for working excepting the graphics
    %Privacy: public structure
                                                       **/
/**
* @brief game definition
*
* Struct for storing the elements of the game.
*/

typedef struct _Game Game;

/**
* @brief creates a game
*
* Creates a new game, allocating memory for
* its spaces and for the structure game itself
* and initializating to null other. It also creates a die.
*
* @author Juan Moreno
* @return Pointer to game if everything wen correctly,
* NULL in other case
*/

Game *game_create();

/**
* @brief adds a space to the game
*
* @author Juan Moreno
* @param game pointer to game.
* @param space pointer to space.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_add_space(Game* game, Space* space);

/**
* @brief adds an object to the game
*
* @author Juan Moreno
* @param game pointer to game.
* @param object pointer to object.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_add_object(Game* game, Object* object);

/**
* @brief calls the game_reader functions
*
* Calls to game create to create a new game and calls
* the game_reader functions to load the game's content from the file.
*
* @author Juan Moreno
* @param game pointer to game.
* @param filename a string containing the name of the file to open.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_create_from_file(Game* game, char* filename);

/**
* @brief executes commands
*
* Calls a callback function executing the command
* defined in it.
*
* @author Juan Moreno
* @param game pointer to game.
* @param cmd the command to be used.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_update(Game* game, T_Command cmd);

/**
* @brief Frees the memory of all the elements in a game
*
* Receives pointer to game and frees the
* memory it occupied.
*
* @author Juan Moreno
* @param game pointer to game.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_destroy(Game* game);

/**
* @brief Checks if the game has ended
*
* @author Juan Moreno
* @param game pointer to game.
* @return BOOL, FALSE if when checking is not correct, if
* it is correct, TRUE.
*/

BOOL   game_is_over(Game* game);

/**
* @brief prints the screen of the game
*
* If game is not pointing to NULL,
* the function prints the screen of the game.
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/

void   game_print_screen(Game* game);

/**
* @brief prints the data of the game
*
* If game is not pointing to NULL,
* the function prints the data of the game.
*
* @author Juan Moreno
* @param game pointer to game.
* @return void function.
*/

void   game_print_data(Game* game);

/**
* @brief gets the spaces of the game
*
* Returns a pointer to a space with a
* determined id.
*
* @author Juan Moreno
* @param game pointer to game
* @param id long int.
* @return the spaces of the game(pointer to space),
* NULL if something goes wrong.
*/

Space* game_get_space(Game* game, Id id);

/**
* @brief gets the location of the player
*
* Returns the id where the player is
* located at that moment.
*
* @author Juan Moreno
* @param game pointer to game
* @return An id representing the player's location.
*/

Id     game_get_player_location(Game* game);

/**
* @brief gets the location of an object
*
* Returns the id where the object is
* located at that moment.
*
* @author Juan Moreno
* @param object pointer to object.
* @return An id representing the player's location.
*/

Id     game_get_object_location(Object* object);

/**
* @brief gets the last value of the die
*
* Returns the value of the game's die last roll.
*
* @author Juan Moreno
* @param game pointer to game.
* @return the last number generated of the die (int).
*/

int    game_get_die_lastroll(Game * game);

/**
* @brief gets the last command
*
* Returns the status of the last command used
*
* @author Juan Moreno
* @param game pointer to game.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_get_last_command_status(Game* game);

/**
* @brief sets a location for an object
*
* Modifies the location where an object
* is placed.
*
* @author Juan Moreno
* @param object pointer to object.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_set_object_location(Object* object, Id id);

/**
* @brief gets the last command selected
*
* Returns the last command used by the player.
*
* @author Juan Moreno
* @param game pointer to game.
* @return #T_Command ==> The last command used by the player.
*/

T_Command game_get_last_command(Game* game);


/* --------------------------------------------------------------------
NEW FUNCTIONS
---------------------------------------------------------------------- */

/**
* @brief gets and object from the game
*
* Returns an object, but this time it will be
* defined with a pointer to game.
*
* @author Juan Moreno
* @param game pointer to game.
* @param i int (i).
* @return pointer to game (object from game struct),
* NULL if something goes wrong.
*/

Object *get_object_from_game(Game *game, int i);

/**
* @brief gets an auxiliary string
*
* Function that returns a string that enables the writing
*
* @author Juan Moreno
* @param game pointer to game.
* @return pointer to game (char string).
*/

char * game_get_aux(Game *game);

/**
* @brief adds a link to the game
*
* It is the function in charge of adding
* links to the game when considering it appropriate.
*
* @author Juan Moreno
* @param game pointer to game.
* @param link pointer to link
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_add_link(Game* game, Link* link);

/**
* @brief gets link of the game
*
* Returns the id of a link doing it in the game
* module.
*
* @author Juan Moreno
* @param game pointer to game.
* @param id long int.
* @return pointer to link.
*/

Link * game_get_link(Game *game, Id id);

/**
* @brief sets location to player
*
* It is the function in charge of setting a principal
* location(id) to the player.
*
* @author Juan Moreno
* @param game pointer to game.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS game_set_player_location(Game* game, Id id);

/**
* @brief gets the player
*
* Function in charge of returning
* the actual player that is playing the game.
*
* @author Juan Moreno
* @param game pointer to game.
* @return pointer to player.
*/

Player *get_player_from_game(Game *game);

/**
* @brief gets die of the game
*
* Returns the value of the die in the game.
*
* @author Juan Moreno
* @param game pointer to game.
* @return pointer to die.
*/

Die *get_die_from_game(Game *game);

/**
* @brief gets the location of an space
*
* Returns the id where the space is located
* at.
*
* @author Juan Moreno
* @param game pointer to game.
* @param position int value.
* @return An id representing the space´s location.
*/

Id game_get_space_id_at(Game* game, int position);

#endif

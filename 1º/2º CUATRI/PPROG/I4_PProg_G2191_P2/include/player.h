/**
* @brief Implements the game player commands
*
* @file player.h
* @author Borja Pérez
* @version 1.6
* @date 09-04-2018
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "inventory.h"

#define MAXPLAYNAME 50  /*!< maximum number of characters for a player name */

/**
* @brief player definition
*
* Struct for storing a player and the elements
* it will use while playing.
*/

typedef struct _Player Player;

/**
* @brief creates a player
*
* It creates a new object initializing
* the variables of the structure.
*
* @author Borja Pérez
* @param id long int.
* @return pointer to player, NULL if something
* goes wrong.
*/

Player * player_create(Id id);

/**
* @brief frees memory
*
* Receives pointer to player and frees the
* memory it occupied.
*
* @author Borja Pérez
* @param p pointer to player.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS player_destroy(Player * p);

/**
* @brief gets the name of a player
*
* Function in charge of showing the name
* of a player that has already been set.
*
* @author Borja Pérez
* @param p pointer to object.
* @return char (name of the player).
*/

char * player_get_name(Player * p);

/**
* @brief gets the id of a player
*
* Function in charge of getting the id of
* an player by using a pointer to it.
*
* @author Borja Pérez
* @param p pointer to player.
* @return Id, NO_ID if object is pointing NULL.
*/

Id player_get_id(Player * p);

/**
* @brief gets the location of an player
*
* Function in charge of getting the location
* of a player and returning it.
*
* @author Borja Pérez
* @param p pointer to player
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id player_get_location(Player * p);

/**
* @brief gets an object
*
* Function in charge of getting the object
* that the player will carry.
*
* @author Borja Pérez
* @param p pointer to player.
* @param position int (position of the object).
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id player_get_object(Player * p, int position);

/**
* @brief gets an inventory
*
* The player has an inventory that enables the player
* to take more than one object.
*
* @author Borja Pérez
* @param p pointer to player.
* @return pointer to inventory (objects).
*/

Inventory * player_get_inventory(Player * p);

/**
* @brief sets name 
*
* Function in charge of changing
* the name of a player.
*
* @author Borja Pérez
* @param p pointer to player.
* @param name char( string for the name of the player).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS player_set_name(Player * p, char * name);

/**
* @brief sets an id for a player
*
* Function in charge of changing a player's id.
*
* @author Borja Pérez
* @param p pointer to player.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS player_set_id(Player * p, Id id);

/**
* @brief sets location
*
* Changes a player's location.
*
* @author Borja Pérez
* @param p pointer to player.
* @param location The id of the player's location.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS player_set_location(Player * p, Id location);

/**
* @brief checks if player has an id
*
* Function in charge of making sure that the player
* is getting an id.
*
* @author Borja Pérez
* @param p pointer to player.
* @param id long int.
* @return BOOL, FALSE if when checking is not correct, if 
* it is correct, TRUE.
*/

BOOL player_has_id(Player *p, Id id);

/**
* @brief sets object
*
* Changes the object carried by a player.
*
* @author Borja Pérez
* @param p pointer to player.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS player_set_object(Player * p, Id id);

/**
* @brief checks if inventory is empty
*
* Function in charge of making sure that the inventory
* is empty using a pointer to player in order to work with other modules
* more easily.
*
* @author Borja Pérez
* @param p pointer to player.
* @return BOOL, FALSE if when checking is not correct, if 
* it is correct, TRUE.
*/

BOOL player_inventory_is_empty(Player *p);

/**
* @brief checks if inventory is full
*
* Function in charge of making sure that the inventory
* is full using a pointer to player in order to work with other modules
* more easily.
*
* @author Borja Pérez
* @param p pointer to player.
* @return BOOL, FALSE if when checking is not correct, if 
* it is correct, TRUE.
*/

BOOL player_inventory_is_full(Player *p);

/**
* @brief removes an object
*
* Deletes an object by using other functions
* prepared for this specific one.
*
* @author Borja Pérez
* @param p pointer to player.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS player_remove_object(Player *p, Id id);
#endif









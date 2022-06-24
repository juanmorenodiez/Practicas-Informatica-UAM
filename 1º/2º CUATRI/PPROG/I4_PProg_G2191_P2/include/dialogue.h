/**
* @brief Includes all the functionality used
* in the dialogue module.
*
* @file dialogue.h
* @author Andrés Mena
* @version 1.0
* @date 29-04-2018
*/

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <stdio.h>
#include "game.h"
#include "types.h"

/**
* @brief shows dialogue when error in spaces
*
* Checks if there is an error in the
* space that the player wants to interact with.
*
* @author Andrés Mena
* @param game pointer to game.
* @param space Id (long int).
* @return pointer to char (string of characters
* that shows a message if there is an error).
*/

char *dialogue_check_space_error(Game *game, Id space);

/**
* @brief shows dialogue when error in spaces and objects
*
* Checks if there is an error in the location
* of spaces and objects.
*
* @author Andrés Mena
* @param oname (pointer to char).
* @return pointer to char (string of characters
* that shows a message if there is an error).
*/

char *dialogue_check_error(char *oname);

/**
* @brief shows dialogue when success in spaces
*
* Checks if there is something wrong with the space
* you want to interact with and shows a message if there
* is no error.
*
* @author Andrés Mena
* @param game pointer to game.
* @param space Id (long int).
* @return pointer to char (string of characters
* that shows a message if there is success).
*/

char *dialogue_check_space_success(Game *game, Id space);

/**
* @brief shows dialogue when success in movements
*
* Checks the different movements and shows a message
* that describes where have you been moved and the name
* of the space.
*
* @author Andrés Mena
* @param game pointer to game.
* @param space Id (long int).
* @param cardinal (char).
* @return pointer to char (string of characters
* that shows a message if there is success).
*/

char *dialogue_movement_success(Game *game, Id space, char *cardinal);

/**
* @brief shows dialogue when success in checking an object
*
* Checks the position of an object and
* shows a message either it is in its original
* position or not.
*
* @author Andrés Mena
* @param object pointer to object.
* @return pointer to char (string of characters
* that shows a message if there is success).
*/

char *dialogue_check_object_success(Object *object);

/**
* @brief shows dialogue when error in movements
*
* Checks the different movements and shows a message
* that tells the player that the movement is
* not allowed if there is an error while checking the movement.
*
* @author Andrés Mena
* @param game pointer to game.
* @param space Id (long int).
* @param cardinal (char).
* @return pointer to char (string of characters
* that shows a message if there is an error).
*/

char *dialogue_movement_error(Game *game, Id space, char *cardinal);

/**
* @brief shows dialogue when throwing the die
*
* Checks if there is any error with the die and
* shows a message with the value of the die.
*
* @author Andrés Mena
* @param die pointer do Die.
* @return pointer to char (string of characters
* that shows a message when throwing the die).
*/

char *dialogue_throw_die(Die *die);

/**
* @brief shows dialogue when error while dropping
* an object
*
* Checks if there is an error when trying to drop
* an object and shows a message.
*
* @author Andrés Mena
* @param oname pointer to char.
* @param game pointer to game.
* @param act_space Id (long int).
* @param j (int value).
* @return pointer to char (string of characters
* that shows a message if there is an error).
*/

char *dialogue_drop_object_error(char *oname, Game *game, Id act_space, int j);

/**
* @brief shows dialogue when success while dropping
* an object
*
* Checks if there is an error when trying to drop
* an object and shows a message if the object has been
* dropped succesfully.
*
* @author Andrés Mena
* @param object pointer to object.
* @param game pointer to game.
* @param act_space Id (long int).
* @return pointer to char (string of characters
* that shows a message if there is success).
*/

char *dialogue_drop_object_success(Object *object, Game *game, Id act_space);

/**
* @brief shows dialogue when error while grasping
* an object
*
* Checks if there is an error when trying to grasp
* an object and shows a message.
*
* @author Andrés Mena
* @param oname pointer to char.
* @param game pointer to game.
* @param act_space Id (long int).
* @param j (int value).
* @return pointer to char (string of characters
* that shows a message if there is an error).
*/

char *dialogue_grasp_object_error(char *oname, Game *game, Id act_space, int j);

/**
* @brief shows dialogue when success while grasping
* an object
*
* Checks if there is an error when trying to grasp
* an object and shows a message if the object has been
* grasped succesfully.
*
* @author Andrés Mena
* @param object pointer to object.
* @param game pointer to game.
* @param act_space Id (long int).
* @return pointer to char (string of characters
* that shows a message if there is success).
*/

char *dialogue_grasp_object_success(Object *object, Game *game, Id act_space);

/**
* @brief shows dialogue when introducing an
* unknown command
*
* Checks if there is an error while introducing
* a command and shows an error message.
*
* @author Andrés Mena
* @return pointer to char (string of characters
* that shows a message if the command is unknown).
*/

char *dialogue_unknown();

/**
* @brief shows dialogue when error while grasping
* an object that is not movable
*
* Checks if there is an error when trying to grasp
* a non-movable object and shows a message.
*
* @author Andrés Mena
* @param oname pointer to char.
* @param game pointer to game.
* @param space_id Id (long int).
* @return pointer to char (string of characters
* that shows a message if there is an error).
*/

char *dialogue_grasp_object_error_movable(char *oname, Game *game, Id space_id);

/**
* @brief shows dialogue when success while turning
* on an object
*
* Checks if there is an error when trying to turn on
* an object and shows a message if the object has been
* turned on succesfully.
*
* @author Andrés Mena
* @param oname pointer to char.
* @return pointer to char (string of characters
* that shows a message if there is success).
*/

char *dialogue_turnon_object_success(char *oname);

/**
* @brief shows dialogue when error while turning on
* an object
*
* Checks if there is an error when trying to turn on
* an object and shows a message.
*
* @author Andrés Mena
* @param oname pointer to char.
* @param j (int value).
* @param k (int value).
* @return pointer to char (string of characters
* that shows a message if there is an error).
*/

char *dialogue_turnon_object_error(char *oname, int j, int k);

/**
* @brief shows dialogue when success while turning
* off an object
*
* Checks if there is an error when trying to turn off
* an object and shows a message if the object has been
* turned off succesfully.
*
* @author Andrés Mena
* @param oname pointer to char.
* @return pointer to char (string of characters
* that shows a message if there is success).
*/

char *dialogue_turnoff_object_success(char *oname);

/**
* @brief shows dialogue when error while turning off
* an object
*
* Checks if there is an error when trying to turn off
* an object and shows a message.
*
* @author Andrés Mena
* @param oname pointer to char.
* @param j (int value).
* @return pointer to char (string of characters
* that shows a message if there is an error).
*/

char *dialogue_turnoff_object_error(char *oname, int j);

/**
* @brief shows dialogue when success while unlocking a door
*
* Checks if there is an error when trying to unlock
* a door
*
* @author Andrés Mena
* @param object pointer to char.
* @param link pointer to char.
* @return pointer to char (string of characters
* that shows a message if there is success).
*/
char *dialogue_unlock_success(char *object, char *link);

/**
* @brief shows dialogue when error while unlocking a door
*
* Checks if there is an error when trying to unlock a door
*shows a message
*
* @author Andrés Mena
* @param object pointer to char.
* @param link pointer to char.
* @param j (int value).
* @param k (int value).
* @return pointer to char (string of characters
* that shows a message if there is an error).
*/
char *dialogue_unlock_error(char *object, char *link, int j, int k);

/**
* @brief shows dialogue when error while moving
*
* Checks if there is an error when trying to make a move
*
* @author Andrés Mena
* @param game pointer to game.
* @param space long int
* @param cardinal pointer to char
* @return pointer to char (string of characters
* that shows a message if there is an error).
*/
char *dialogue_movement_link_error(Game *game, Id space, char *cardinal);
#endif

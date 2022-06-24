/**
* @brief Contains the command list and the declaration
* of the get user input function
*
* It is composed by the enumeration that lists all the commands
* available in the game. These are the actions that a player can
* make when playing the game.
*
* @file command.h
* @author Juan Moreno
* @version 3.0
* @date 07-04-2018
*/

#ifndef COMMAND_H
#define COMMAND_H

/**
* @brief command list
*/

typedef enum enum_Command {
  NO_CMD = -1,  /*!< error */
  UNKNOWN,  /*!< unknown command */
  EXIT,  /*!< exit command */
  GRASP,  /*!< grasp command */
  DROP,  /*!< drop command */
  THROW,  /*!< throw command */
  CHECK,  /*!< check command */
  MOVE,  /*!< move command */
  TURNON, /*!< swithcing on command */
  TURNOFF, /*!< swithcing off command */
  UNLOCK,
  SAVE,
  LOAD
} T_Command;

/**
* @brief gets the command selected
*
* Detects the command a user has written and converts
* it to a numerical code.
*
* @return #T_Command ==> Number from -1 to 9 with the
* command code.
*/

T_Command command_get_user_input();

#endif

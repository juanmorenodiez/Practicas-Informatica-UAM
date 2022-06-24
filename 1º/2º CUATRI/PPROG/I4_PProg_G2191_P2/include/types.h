/**
* @brief Defines some structures and enumerations
*
* @file types.h
* @author Juan Moreno
* @version 2.0
* @date 07-04-2018
*/

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000   /*!< defines a max number for the word */
#define NO_ID -1   /*!< defines when id is wrong as -1 */
#define MAX_DESCRIPTION 128  /*!< maximum description for an element */
#define MAX_LONG_DESCRIPTION 512  /*!< maximum description for a long element */

/**
* @brief id: long int variable
*/

typedef long Id;

/**
* @brief boolean error list
*/

typedef enum {
  FALSE,    /*!< false condition */
  TRUE    /*!< true condition */
} BOOL;

/**
* @brief status error list
*/

typedef enum {
  ERROR,    /*!< error */
  OK    /*!< No error */
} STATUS;

/**
* @brief directons list
*/

typedef enum {
  N,  /*!< north direction */
  S,  /*!< south direction */
  E,  /*!< east direction */
  W  /*!< west direction */
} DIRECTION;

/**
* @brief status of link
*/

typedef enum {
  OPEN,  /*!< opened link */
  CLOSE  /*!< closed link */
} LINK_ST;

#endif

#ifndef DIE_H
#define DIE_H

/**
* @brief generates a die
*
* This module creates a dice that will generate a random
* number between 1 and 6 that will be the number of spaces that
* an object should move.
*
* @file die.h
* @author Juan Moreno
* @version 2.0
* @date 07-04-2018
*/

#include "types.h"

/**
* @brief die with id and last number
*
* Struct for storing a die that will show a random number
* and get the last roll.
*/

typedef struct _Die Die;

/**
* @brief creates a die
*
* It creates a new inventory by initializing
* the variables of the structure and allocating
* mamory for a new die.
*
* @author Juan Moreno
* @param id long int.
* @return pointer to die.
*/

Die *die_create(Id id);

/**
* @brief frees memory
*
* Receives pointer to die and frees the
* memory it occupied.
* 
* @author Juan Moreno
* @param d pointer to die.
* @return VOID FUNCTION, FREES MEMORY ONLY.
*/

void die_destroy(Die *d);

/**
* @brief returns the id of a die
*
* Function in charge of returning the id of a die
* already created.
*
* @author Juan Moreno
* @param d pointer to die.
* @return pointer to die(id of the die).
*/

Id die_get_id(Die *d);

/**
* @brief returns the last value of the die
*
* Function in charge of returning the last roll generated
* by the die in orther to keep that value.
*
* @author Juan Moreno
* @param d pointer to die.
* @return Number that the die rolled last time.
*/

int die_get_lastroll(Die *d);

/**
* @brief generates a number between 1 and 6
*
* Rolls a die, giving a random number between 1
* and 6 and storing it in lastroll.
*
* @author Juan Moreno
* @param d pointer to die.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS die_roll(Die *d);

/**
* @brief prints the id and last roll of a die
*
* Function in charge of printing the last roll of a die
* and its id in order to check that it is working correctly.
*
* @author Juan Moreno
* @param d pointer to die.
* @return VOID FUNCTION, ONLY PRINTS ID AND NUMBER OF THE DIE
* BY CALLING die_get_lastroll.
*/

void die_print_content(Die *d);

#endif


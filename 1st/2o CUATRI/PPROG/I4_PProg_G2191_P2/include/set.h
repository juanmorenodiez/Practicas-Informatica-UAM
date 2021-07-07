#ifndef SET_H
#define SET_H

/**
* @brief helps us manage other modules with a better
* organisation using its functions to change values.
*
* The functions of the set module, will help us in other
* modules. By using the functions of this module, we will 
* be able to modify and change values such as the id of an 
* object and we will be able to do it in a more organised way.
* 
* @file set.h
* @author Juan Moreno
* @version 2.0
* @date 05-04-2018
*/

#include "types.h"

/**
* @brief id and number of ids
*
* Struct for managing the values and adding ids
* by using an id and the number of ids.
*/

typedef struct _Set Set;

/**
* @brief creates a set
*
* It creates a new set, if id is -1(NO_ID),
* NULL is returned, if not, memory for a new set is
* reserved and created. If anything goes wrong, it
* returns NULL.
*
* @author Juan Moreno
* @return Pointer to set, NULL if something
* goes wrong.
*/

Set *set_create();

/**
* @brief frees memory
*
* Receives pointer to set and frees the
* memory it occupied.
*
* @author Juan Moreno
* @param set pointer to set.
* @return VOID FUNCTION TYPE.
*/

void set_destroy(Set * set);

/**
* @brief adds a value defined by the set
*
* It is the function in charge of adding
* sets to other functions that require it.
*
* @author Juan Moreno
* @param id (long int).
* @param set pointer to set.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS set_add_value(Id id, Set *set);

/**
* @brief deletes a value already defined
*
* Function in charge of deleting sets when
* you are willing to do it and when it is necessary.
*
* @author Juan Moreno
* @param id long int.
* @param set pointer to set.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS set_delete_value(Id id, Set *set);

/**
* @brief gets the number of ids
*
* Function in charge of returning the number of ids
* by using that will be used when considered useful
* and convenient.
*
* @author Juan Moreno
* @param set pointer to set.
* @return pointer to set (int) referring to the number
* of ids.
*/

int set_get_nids(Set * set);

/**
* @brief gets an id using a set
*
* Function in which the Id of
* the object in a received position is returned.
*
* @author Juan Moreno
* @param set pointer to set.
* @param position position of the set(int).
* @return Id, NO_ID if set is pointing NULL.
*/

Id get_set (Set *set, int position);

/**
* @brief checks the id of a set
*
* It is the function that will be used in other modules
* to check if that function is using an id by passing two
* arguments: a pointer to set and an id.
*
* @author Juan Moreno
* @param set pointer to set.
* @param id long int.
* @return BOOL, FALSE if when checking is not correct, if 
* it is correct, TRUE.
*/

BOOL set_has_id(Set *set, Id id);

/**
* @brief Prints a list with the ids of the elements of a list
*
* Function in charge of printing the set,
* in order to check that everything is working correctly.
*
* @author Juan Moreno
* @param set pointer to set.
* @return VOID FUNCTION TYPE, IT ONLY PRINTS THE LINE WE 
* ORDERED IT TO PRINT.
*/

void set_print_values(Set *set);

#endif

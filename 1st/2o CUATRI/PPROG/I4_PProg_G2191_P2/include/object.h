/**
* @brief Implements the game object commands
*
* @file object.h
* @author Juan Moreno
* @version 1.1
* @date 07-04-2018
*/

#ifndef GAME_OBJECT_H

#define GAME_OBJECT_H

#include <stdio.h>
#include "types.h"

#define MAXOBJNAME 30  /*!< defines maximum number of objects */

/**
* @brief object of the game
*
* Struct for storing the different variables that an object should have
*/

typedef struct _Object Object;


/**
* @brief creates an object
*
* It creates a new object initializing
* the variables of the structure, checks is something goes
* wrong and if it does go wrong, returns NULL.
*
* @author Juan Moreno
* @param id long int.
* @return Pointer to object, NULL if something
* goes wrong.
*/

Object * object_create(Id id);

/**
* @brief frees memory
*
* Receives pointer to object and frees the
* memory it occupied.
*
* @author Juan Moreno
* @param o pointer to object.
* @return void function.
*/

void object_destroy(Object * o);

/**
* @brief gets the id of an object
*
* Function in charge of getting the id of
* an object by using a pointer to object.
*
* @author Juan Moreno
* @param o pointer to object.
* @return Id, NO_ID if object is pointing NULL.
*/

Id object_get_id(Object * o);

/**
* @brief gets the name of an object
*
* Function in charge of showing the name
* of an object that has already been set.
*
* @author Juan Moreno
* @param o pointer to object.
* @return char (name of the object).
*/

char * object_get_name(Object * o);

/**
* @brief gets the location of an object
*
* Function in charge of getting the location
* of an object and returning it.
*
* @author Juan Moreno
* @param o pointer to object.
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id object_get_location(Object * o);

/**
* @brief sets the name of an object
*
* Modifies an object's name in order to set
* an specific name por each object.
*
* @author Juan Moreno
* @param o pointer to object.
* @param name name of the object(char).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_name(Object * o, char * name);

/**
* @brief sets an id for an object
*
* It spececifically changes the id of a
* particular object.
*
* @author Juan Moreno
* @param o pointer to object.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_id(Object * o, Id id);

/**
* @brief sets location
*
* Changes an object's location ingame
*
* @author Juan Moreno
* @param o pointer to object.
* @param id id of the object's location.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_location(Object * o, Id id);

/**
* @brief prints an object
*
* Writes the object data, used for debugging.
*
* @author Juan Moreno
* @param o pointer to object.
* @param f file to write the object.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_print(Object * o, FILE * f);

/**
* @brief gets description
*
* Changes the description of the object that has already
* been created.
*
* @author Juan Moreno
* @param o pointer to object.
* @return the description of the object (char).
*/

char * object_get_original_description(Object * o);

/**
* @brief sets description
*
* It prepares the description of the objects which is
* defined in data.dat file. Principally describes what the
* objects do.
*
* @author Juan Moreno
* @param o pointer to object.
* @param description char (description of the object).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_original_description(Object * o, char * description);

/**
* @brief sets position
*
* It prepares the position of the objects which is
* defined in data.dat file. Principally defines a position
* for the object.
*
* @author Juan Moreno
* @param o pointer to object.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_original_position(Object * o, Id id);

/**
* @brief gets description
*
* It returns the description that has already been set
* for an object.
*
* @author Juan Moreno
* @param o pointer to object.
* @return pointer to char, string of characters that
* return the description of the object.
*/

Id object_get_original_position(Object * o);

/**
* @brief sets description
*
* It prepares the description of an object that
* has been moved.
*
* @author Juan Moreno
* @param o pointer to object.
* @param description pointer to char.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_moved_description(Object * o, char * description);

/**
* @brief sets status of mobility
*
* It sets a new status to objects, defines if an
* object can me movable or not.
*
* @author Juan Moreno
* @param o pointer to object.
* @param st Boolean
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_prop_Movable(Object *o, BOOL st);

/**
* @brief gets the mobility status
*
* Function that returns whether an object is movable or not.
*
* @author Juan Moreno
* @param o pointer to object.
* @return BOOL, FALSE if when checking is not correct, if
* it is correct, TRUE.
*/

BOOL object_get_prop_Movable(Object *o);

/**
* @brief sets status of being moved
*
* Defines an object that is movable and sets if
* that object is moved or not.
*
* @author Juan Moreno
* @param o pointer to object.
* @param st Boolean
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_prop_Moved(Object *o, BOOL st);

/**
* @brief gets the moved object
*
* Function that returns the moved object that you already
* know that can be movable.
*
* @author Juan Moreno
* @param o pointer to object.
* @return BOOL, FALSE if when checking is not correct, if
* it is correct, TRUE.
*/

BOOL object_get_prop_Moved(Object *o);

/**
* @brief sets status of hidden
*
* It sets a new status to objects, a hidden
* status that allows the player to hide objects.
*
* @author Juan Moreno
* @param o pointer to object.
* @param st Boolean
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_prop_Hidden(Object *o, BOOL st);

/**
* @brief gets the hidden status
*
* Function that returns a hidden object.
*
* @author Juan Moreno
* @param o pointer to object.
* @return BOOL, FALSE if when checking is not correct, if
* it is correct, TRUE.
*/

BOOL object_get_prop_Hidden(Object *o);

/**
* @brief sets status of ilumination
*
* It sets a new status to objects, an ilumination
* status that allows the player to iluminate objects.
*
* @author Juan Moreno
* @param o pointer to object.
* @param st Boolean
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_prop_Illuminate(Object *o, BOOL st);

/**
* @brief gets the ilumination status
*
* Function that returns an iluminated object.
*
* @author Juan Moreno
* @param o pointer to object.
* @return BOOL, FALSE if when checking is not correct, if
* it is correct, TRUE.
*/

BOOL object_get_prop_Illuminate(Object *o);

/**
* @brief sets status of switching on
*
* It sets a new status to objects, objects that can be
* iluminated, should also be able to be turned on and off
* with the help of the callback commands and this function.
*
* @author Juan Moreno
* @param o pointer to object.
* @param st Boolean
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_prop_SwitchedOn(Object *o, BOOL st);

/**
* @brief gets the switched on status
*
* Function that returns a status that can be iluminated
* and also is switched on.
*
* @author Juan Moreno
* @param o pointer to object.
* @return BOOL, FALSE if when checking is not correct, if
* it is correct, TRUE.
*/

BOOL object_get_prop_SwitchedOn(Object *o);

/**
* @brief sets status of opening
*
* It sets a new status to objects, with this
* function, objects can be used to open other
* objects.
*
* @author Juan Moreno
* @param o pointer to object.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS object_set_prop_Open(Object *o, Id id);

/**
* @brief gets the opened object
*
* It gets the position of the objects which is
* defined in data.dat file that can be opened.
*
* @author Juan Moreno
* @param o pointer to object.
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id object_get_prop_Open(Object *o);

/**
* @brief gets description
*
* Changes the description of the object that has already
* been created.
*
* @author Juan Moreno
* @param o pointer to object.
* @return the description of the object (char).
*/
char * object_get_moved_description(Object * o);


#endif

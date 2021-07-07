/**
* @brief Defines the space related function
*
* @file space.h
* @author Dan Roife
* @version 1.1
* @date 07-04-2018
*/

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "object.h"
#include "set.h"

/**
* @brief spaces of the game
*
* Struct for storing the different variables and
* characteristics that spaces should have.
*/

typedef struct _Space Space;

#define MAX_SPACES 100  /*!< maximum number of spaces */
#define FIRST_SPACE 1  /*!< first space of the game */

/**
* @brief allocates memory for a new space
*
* It creates a new space initializing
* the variables of the structure, checks is something goes
* wrong and if it does go wrong, returns NULL.
*
* @author Dan Roife
* @param id (long int).
* @return Pointer to space, NULL if something
* goes wrong.
*/

Space* space_create(Id id);

/**
* @brief frees memory
*
* Receives pointer to space and frees the
* memory it occupied.
*
* @author Dan Roife
* @param space pointer to space.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_destroy(Space* space);

/**
* @brief gets the id of a space
*
* Function in charge of getting the id of
* a space by using a pointer to it.
*
* @author Dan Roife
* @param space pointer to space.
* @return Id, NO_ID if space is pointing NULL.
*/

Id space_get_id(Space* space);

/**
* @brief gets number
*
* Function in charge of getting the
* number of objects that are located in a
* space.
*
* @author Dan Roife
* @param space pointer to space.
* @return int (number of objects).
*/

int space_get_object_number(Space* space);

/**
* @brief sets the name of a space
*
* Modifies a space's name in order to set
* a name for that space.
*
* @author Dan Roife
* @param space pointer to space.
* @param name char (name of the space).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_name(Space* space, char* name);

/**
* @brief gets the name of a space
*
* Function in charge of showing the name
* of a space that has already been set.
*
* @author Dan Roife
* @param space pointer to space.
* @return char (string that contains the name of the space).
*/

const char* space_get_name(Space* space);

/**
* @brief sets location of spaces
*
* Modifies the northern link with another space.
*
* @author Dan Roife
* @param space pointer to space.
* @param id (long int).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_north(Space* space, Id id);

/**
* @brief gets location of spaces
*
* Returns the northern space's id.
*
* @author Dan Roife
* @param space pointer to space.
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id space_get_north(Space* space);

/**
* @brief sets location of spaces
*
* Modifies the southern link with another space.
*
* @author Dan Roife
* @param space pointer to space.
* @param id (long int).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_south(Space* space, Id id);

/**
* @brief gets location of spaces
*
* Returns the southern space's id.
*
* @author Dan Roife
* @param space pointer to space.
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id space_get_south(Space* space);

/**
* @brief sets location of spaces
*
* Modifies the eastern link with another space.
*
* @author Dan Roife
* @param space pointer to space.
* @param id (long int).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_east(Space* space, Id id);

/**
* @brief gets location of spaces
*
* Returns the eastern space's id.
*
* @author Dan Roife
* @param space pointer to space.
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id space_get_east(Space* space);

/**
* @brief sets location of spaces
*
* Modifies the western link with another space.
*
* @author Dan Roife
* @param space pointer to space.
* @param id (long int).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_west(Space* space, Id id);

/**
* @brief gets location of spaces
*
* Returns the western space's id.
*
* @author Dan Roife
* @param space pointer to space.
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id space_get_west(Space* space);

/**
* @brief sets a graphic description
*
* Modifies a piece of the gdesc in a space.
*
* @author Dan Roife
* @param space pointer to space.
* @param c string with graphic description.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_gdesc1(Space* space, char *c);

/**
* @brief returns the graphic description
*
* Returns a space's first piece of graphic description.
*
* @author Dan Roife
* @param space pointer to space.
* @return char (a string containing the first piece
* of the graphic description).
*/

char * space_get_gdesc1(Space* space);

/**
* @brief sets a graphic description
*
* Modifies a piece of the gdesc in a space.
*
* @author Dan Roife
* @param space pointer to space.
* @param c string with graphic description.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_gdesc2(Space* space, char *c);

/**
* @brief returns the graphic description
*
* Returns a space's second piece of graphic description.
*
* @author Dan Roife
* @param space pointer to space.
* @return char (a string containing the second piece
* of the graphic description).
*/

char * space_get_gdesc2(Space* space);

/**
* @brief sets a graphic description
*
* Modifies a piece of the gdesc in a space.
*
* @author Dan Roife
* @param space pointer to space.
* @param c string with graphic description.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_gdesc3(Space* space, char *c);

/**
* @brief returns the graphic description
*
* Returns a space's third piece of graphic description.
*
* @author Dan Roife
* @param space pointer to space.
* @return char (a string containing the third piece
* of the graphic description).
*/

char * space_get_gdesc3(Space* space);

/**
* @brief sets an object for a space
*
* Adds a new id to the object set in
* the space.
*
* @author Dan Roife
* @param space pointer to space.
* @param o pointer to object.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_object(Space* space, Object * o);

/**
* @brief gets an object from a space
*
* Returns a space's set where the ids
* of the objects in the space are saved.
*
* @author Dan Roife
* @param space pointer to space.
* @return #Set ==> The space's set
*/

Set * space_get_object(Space* space);

/**
* @brief sets description
*
* Adds a new description for an specific
* space.
*
* @author Dan Roife
* @param space pointer to space.
* @param description char (description of the space).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_short_description(Space* space, char* description);

/**
* @brief gets description
*
* Returns a char string that describe the
* space.
*
* @author Dan Roife
* @param space pointer to space.
* @return pointer to space (char string).
*/

char * space_get_short_description(Space* space);

/**
* @brief sets description
*
* Adds a new description for an specific
* space.
*
* @author Dan Roife
* @param space pointer to space.
* @param description char (description of the space).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_long_description(Space* space, char* description);

/**
* @brief gets description
*
* Returns a char string that describe the
* space.
*
* @author Dan Roife
* @param space pointer to space.
* @return pointer to space (char string).
*/

char * space_get_long_description(Space* space);

/**
* @brief prints the spaces
*
* Function in charge of printing spaces,
* in order to check that everything is working correctly.
*
* @author Dan Roife
* @param space pointer to space
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_print(Space* space);

/**
* @brief frees memory
*
* Receives pointer to space and frees the
* memory it occupied. I this case, it destroys
* an object from a space.
*
* @author Dan Roife
* @param s pointer to space.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_object_destroy(Space * s, Id id);

/**
* @brief checks if space is linked
*
* It determines if a space is linked to another one
* by using the "link" module functions.
*
* @author Dan Roife
* @param s pointer to space.
* @return BOOL, FALSE if when checking is not correct, if
* it is correct, TRUE.
*/

BOOL space_is_linked(Space *s);

/**
* @brief sets ilumination
*
* Adds a new functionality that enables
* us to iluminate spaces.
*
* @author Dan Roife
* @param space pointer to space.
* @param iluminate Boolean.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_iluminate(Space *space, BOOL iluminate);

/**
* @brief returns the iluminated space
*
* It is the function in charge of returning
* a iluminated space that has already been set.
*
* @author Dan Roife
* @param space pointer to space.
* @return BOOL, FALSE if when checking is not correct, if
* it is correct, TRUE.
*/

BOOL space_get_iluminate(Space *space);

/**
* @brief gets description
*
* returns a char string with the graphic description.
*
* @author Juan Moreno
* @param s pointer to space.
* @param line int value.
* @return pointer to char.
*/

char * space_get_gdesc_line(Space * s, int line);

/**
* @brief sets description
*
* Sets a status for the graphic description.
*
* @author Juan Moreno
* @param s pointer to space.
* @param line int value.
* @param c pointer to char.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_gdesc_line(Space * s, int line, char * c);

/**
* @brief sets location of spaces
*
* Modifies the upper link with another space.
*
* @author Dan Roife
* @param space pointer to space.
* @param id (long int).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_up(Space* space, Id id);

/**
* @brief sets location of spaces
*
* Modifies down link with another space.
*
* @author Dan Roife
* @param space pointer to space.
* @param id (long int).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS space_set_down(Space* space, Id id);

/**
* @brief gets location of spaces
*
* Returns the upper space's id.
*
* @author Dan Roife
* @param space pointer to space.
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id space_get_up(Space* space);

/**
* @brief gets location of spaces
*
* Returns the down space's id.
*
* @author Dan Roife
* @param space pointer to space.
* @return Id, NO_ID if inventory is pointing NULL.
*/


Id space_get_down(Space* space);

#endif

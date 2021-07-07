#ifndef LINK_H
#define LINK_H

/**
* @brief links spaces
*
* Module that links the spaces of the game
* by putting together the ones who are: "death",
* "goose" and "bridge". It also links spaces which
* distance is one space between them.
*
* @file link.h
* @author Andrés Mena 
* @version 1.1
* @date 07-04-2018
*/

#include <stdio.h>
#include "types.h"

/**
* @brief link definition
*
* Struct for storing a link with its
* properties.
*/
typedef struct _Link Link;

/**
* @brief creates a link
*
* It creates a new link, if id is -1(NO_ID),
* NULL is returned, if not, memory for a new link is
* reserved and created. If anything goes wrong, it
* returns NULL.
*
* @author Andrés Mena 
* @param id long int.
* @return pointer to link, NULL if something
* goes wrong.
*/

Link *link_create(Id id);

/**
* @brief frees memory
*
* Receives pointer to link and frees the
* memory it occupied.
*
* @author Andrés Mena 
* @param link pointer to link.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS link_destroy(Link *link);

/**
* @brief sets an id
*
* If there is an error, ERROR is returned, if not,
* it establishes an id for the link.
*
* @author Andrés Mena 
* @param link pointer to link.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS link_set_id (Link *link, Id id);

/**
* @brief sets a name
*
* If there is an error, ERROR is returned, if not,
* it copies the char string into the link name.
*
* 
* @author Andrés Mena 
* @param link pointer to link.
* @param name name (char string).
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS link_set_name (Link *link, char *name);

/**
* @brief sets link number one
*
* If there is an error, ERROR is returned, if not,
* it gives an id to the first link compared.
*
* @author Andrés Mena 
* @param link pointer to link.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS link_set_link1 (Link *link, Id id);

/**
* @brief sets link number two
*
* If there is an error, ERROR is returned, if not,
* it gives an id to the second link compared.
*
* @author Andrés Mena 
* @param link pointer to link.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS link_set_link2 (Link *link, Id id);

/**
* @brief sets the status of the link
*
* If the link is open, it returns OPEN, if not,
* the link is not working and returns CLOSE.
*
* @author Andrés Mena 
* @param link pointer to link.
* @param st link status.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS link_set_status(Link *link, LINK_ST st);

/**
* @brief gets id of the link
*
* Returns the id of the link, if ID = NO_ID(-1),
* gives ERROR and returns NO_ID.
*
* @author Andrés Mena 
* @param link pointer to link.
* @return Id, NO_ID if link is pointing NULL.
*/

Id link_get_id (Link *link);

/**
* @brief gets id of the link number one
*
* Returns the id of the link number one compared, if ID = NO_ID(-1),
* gives ERROR and returns NO_ID.
*
* @author Andrés Mena 
* @param link pointer to link.
* @return Id, NO_ID if link is pointing NULL.
*/

Id link_get_link1(Link *link);

/**
* @brief gets id of the link number two
*
* Returns the id of the link number two, if ID = NO_ID(-1),
* gives ERROR and returns NO_ID.
*
* @author Andrés Mena 
* @param link pointer to link.
* @return Id, NO_ID if link is pointing NULL.
*/

Id link_get_link2(Link *link);

/**
* @brief gets name of the link
*
* Returns a constant string of characters
* which will be the name of the link.
*
* @author Andrés Mena 
* @param link pointer to link.
* @return constant string of characters.
*/

const char *link_get_name(Link *link);

/**
* @brief gets the status of the link
*
* If there is an error, CLOSE is returned, normally
* it will return the OPEN status because it will be
* working properly.
*
* @author Andrés Mena 
* @param link pointer to link.
* @return LINK STATUS, CLOSE if argument received is NULL,
* if not, OPEN.
*/

LINK_ST link_get_status(Link *link);

/**
* @brief prints links
*
* Function in charge of printing the link,
* in order to check that everything is working correctly by
* calling some of its functions.
*
* @author Andrés Mena 
* @param link pointer to link.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS link_print(Link* link);

/**
* @brief gets key to open link
*
* Function in charge of returning the key
* that is used to open a link.
*
* @author Andrés Mena
* @param link pointer to link.
* @return Id, NO_ID if object is pointing NULL.
*/

Id link_get_key (Link *link);

/**
* @brief sets key to open link
*
* Function that it is used to set a link to the key
* that enables us to open that link with the key.
*
* @author Andrés Mena
* @param link pointer to link.
* @param key long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS link_set_key(Link *link, Id key);

#endif

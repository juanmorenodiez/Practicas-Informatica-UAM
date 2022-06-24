#ifndef INVENTORY_H
#define INVENTORY_H

/**
* @brief organises the objects in a backpack
*
* This module helps the organisation and the managing
* of the objects by using different functions that
* enables the player to work with an inventory of
* objects.
* 
* @file inventory.h
* @author Juan Moreno
* @version 1.0
* @date 05-04-2018
*/

#include "types.h"
#include "object.h"
#include "set.h"

/**
* @brief set and max objects.
*
* Struct for organising the objects using a pointer to set
* and a maximum number of objects(int).
*/

typedef struct _Inventory Inventory;

/**
* @brief creates an inventory
*
* It creates a new inventory initializing
* the variables of the structure, checks is something goes
* wrong and if it does go wrong, returns NULL.
*
* @author Juan Moreno
* @return Pointer to inventory, NULL if something
* goes wrong.
*/

Inventory* inventory_create();

/**
* @brief frees memory
*
* Receives pointer to inventory and frees the
* memory it occupied.
*
* @author Juan Moreno
* @param inv pointer to inventory.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS inventory_destroy(Inventory *inv);

/**
* @brief adds an id
*
* It is the function in charge of adding
* ids to the inventory by using the appropriate
* set function.
*
* @author Juan Moreno
* @param inv pointer to inventory.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS inventory_add_id(Inventory *inv, Id id); 

/**
* @brief deletes and id
*
* Function in charge of deleting and id
* of the inventory that you have already added when
* it is necessary.
*
* @author Juan Moreno
* @param inv pointer to inventory.
* @param id long int.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS inventory_delete_id(Inventory *inv, Id id);

/**
* @brief gets the id of an object
*
* Function in charge of getting an object
* by using its id, that id is selected with
* a position (int).
*
* @author Juan Moreno
* @param inv pointer to inventory.
* @param position position of the object (int).
* @return Id, NO_ID if inventory is pointing NULL.
*/

Id inventory_get_object(Inventory *inv, int position);

/**
* @brief checks if there is an object in the inventory
*
* Function that, by calling the function: set_has_id
* can check that there is an object in the inventory
* using its id.
*
* @author Juan Moreno
* @param inv pointer to inventory.
* @param id long int.
* @return BOOL, FALSE if when checking is not correct, if 
* it is correct, TRUE.
*/

BOOL inventory_has_object(Inventory *inv, Id id);

/**
* @brief gets and id using pointer to set
*
* Function in which we will get
* the set of ids by using our pointer to set
* which is defined in the data structure.
*
* @author Juan Moreno
* @param inv pointer to inventory.
* @return Pointer to inventory(set of ids).
*/

Set *inventory_get_set(Inventory *inv);

/**
* @brief prints the inventory
*
* Function in charge of printing the inventory,
* in order to check that everything is working correctly by
* calling the function in set module that prints the values.
*
* @author Juan Moreno
* @param inv pointer to inventory.
* @return STATUS, ERROR if argument received is NULL,
* if not, OK.
*/

STATUS inventory_print(Inventory *inv);

/**
* @brief checks if the inventory is empty
*
* Function that will help us in other functions that need to
* check if there is any object in the inventory.
*
* @author Juan Moreno
* @param inv pointer to inventory.
* @return BOOL, FALSE if when checking is not correct, if 
* it is correct, TRUE.
*/

BOOL inventory_is_empty(Inventory *inv);

/**
* @brief checks if the inventory is full
*
* Function that will help us in other functions that need to
* check if the entire inventory is full of objects
*
* @author Juan Moreno
* @param inv pointer to inventory.
* @return BOOL, FALSE if when checking is not correct, if 
* it is correct, TRUE.
*/

BOOL inventory_is_full(Inventory *inv);

#endif

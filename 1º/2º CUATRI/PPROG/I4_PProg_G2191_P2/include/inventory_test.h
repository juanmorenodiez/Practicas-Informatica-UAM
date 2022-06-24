/**
 * @brief It declares the tests for the inventory module
 *
 * @file inventory_test.h
 * @author Andres Mena
 * @version 2.0
 * @date 01-04-2018
 * @copyright GNU Public License
 */

#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H

/**
 * @test Test inventory creation
 * @pre link ID
 * @post Non NULL pointer to inventory
 */
void test1_inventory_create();

/**
 * @test Test adding id to inventory
 * @pre NULL pointer to inventory
 * @post STATUS == ERROR
 */
void test1_inventory_add_id();

/**
 * @test Test adding id to inventory
 * @pre NULL pointer to inventory and NO_ID
 * @post STATUS == ERROR
 */
void test2_inventory_add_id();

/**
 * @test Test adding id to inventory
 * @pre Pointer to inventory and NO_ID
 * @post STATUS == ERROR
 */
void test3_inventory_add_id();

/**
 * @test Test adding id to inventory
 * @pre Pointer to inventory and ID
 * @post STATUS == OK
 */
void test4_inventory_add_id();

/**
 * @test Test adding id to inventory
 * @pre Pointer to inventory and ID (full inventory)
 * @post STATUS == ERROR
 */
void test5_inventory_add_id();

/**
 * @test Test getting set from inventory
 * @pre NULL pointer to inventory
 * @post NULL set pointer
 */
void test1_inventory_get_set();

/**
 * @test Test getting set from inventory
 * @pre Pointer to inventory
 * @post non NULL set pointer
 */
void test2_inventory_get_set();

/**
 * @test Test deleting id from inventory
 * @pre NULL pointer to inventory and NO_ID
 * @post ERROR
 */
void test1_inventory_delete_id();

/**
 * @test Test deleting id from inventory
 * @pre NULL pointer to inventory and ID
 * @post ERROR
 */
void test2_inventory_delete_id();

/**
 * @test Test deleting id from inventory
 * @pre Pointer to inventory and id
 * @post OK
 */
void test3_inventory_delete_id();

/**
 * @test Test destroying inventory
 * @pre NULL pointer to inventory
 * @post ERROR
 */
void test1_inventory_destroy();

/**
 * @test Test destroying inventory
 * @pre Pointer to inventory
 * @post OK
 */
void test2_inventory_destroy();

/**
 * @test Test printing inventory
 * @pre NULL pointer to inventory
 * @post ERROR
 */
void test1_inventory_print();

/**
 * @test Test if inventory is full
 * @pre NULL pointer to inventory
 * @post BOOL == FALSE
 */
void test1_inventory_is_full();

/**
 * @test Test if inventory is full
 * @pre Ponter to inventory (not full)
 * @post BOOL == FALSE
 */
void test2_inventory_is_full();

/**
 * @test Test if inventory is empty
 * @pre NULL Ponter to inventory
 * @post BOOL == FALSE
 */
void test1_inventory_is_empty();

/**
 * @test Test if inventory is empty
 * @pre Ponter to inventory (with no objects)
 * @post BOOL == FALSE
 */
void test2_inventory_is_empty();

/**
 * @test Test if inventory is empty
 * @pre Ponter to inventory (with objects)
 * @post BOOL == TRUE
 */
void test3_inventory_is_empty();

/**
 * @test Test getting objects from inventory
 * @pre NULL pointer to inventory
 * @post NO_ID
 */
void test1_inventory_get_object();

/**
 * @test Test getting objects from inventory
 * @pre Pointer to inventory with object
 * @post id of object
 */
void test2_inventory_get_object();

#endif

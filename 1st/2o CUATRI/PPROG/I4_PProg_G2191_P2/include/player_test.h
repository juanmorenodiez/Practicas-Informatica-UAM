/**
 * @brief It declares the tests for the player module
 *
 * @file player_test.h
 * @author Andrés Mena
 * @version 2.0
 * @date 01-04-2018
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

#include <stdio.h>
#include "types.h"

/**
 * @test Test player creation
 * @pre ID
 * @post Non NULL pointer to player
 */
 void test1_player_create();

 /**
  * @test Test player creation
  * @pre Player ID
  * @post Player_ID == Supplied player Id
  */
 void test2_player_create();

 /**
  * @test Test player creation
  * @pre Player ID
  * @post Player location == 0
  */
 void test3_player_create();

 /**
  * @test Test player creation
  * @pre NULL pointer to player
  * @post STATUS == ERROR
  */
 void test1_player_destroy();

 /**
  * @test Test player creation
  * @pre Pointer to player
  * @post STATUS == OK
  */
 void test2_player_destroy();

 /**
  * @test Test if player has id
  * @pre NULL pointer to player
  * @post BOOL == FALSE
  */
 void test1_player_has_id();

 /**
  * @test Test if player has id
  * @pre Pointer to player and id
  * @post BOOL == FALSE
  */
 void test2_player_has_id();

 /**
  * @test Test if player has id
  * @pre Pointer to player and id
  * @post BOOL == TRUE
  */
 void test3_player_has_id();

 /**
  * @test Test player inventory
  * @pre NULL pointer to player
  * @post NULL
  */
 void test1_player_get_inventory();

 /**
  * @test Test player inventory
  * @pre Pointer to player and inventory
  * @post inventory not NULL
  */
 void test2_player_get_inventory();

 /**
  * @test Test getting objects from player
  * @pre NULL pointer to player
  * @post NO_ID
  */
 void test1_player_get_object();

 /**
  * @test Test getting objects from player
  * @pre Pointer to player (with object)
  * @post object ID
  */
 void test2_player_get_object();

 /**
  * @test Test setting objects to player
  * @pre NULL pointer to player
  * @post ERROR
  */
 void test1_player_set_object();

 /**
  * @test Test setting objects to player
  * @pre Pointer to player and id
  * @post OK
  */
 void test2_player_set_object();

 /**
  * @test Test removing objects from player
  * @pre NULL pointer to player
  * @post ERROR
  */
 void test1_player_remove_object();

 /**
  * @test Test removing objects from player
  * @pre Pointer to player (with objects)
  * @post OK
  */
 void test2_player_remove_object();
#endif

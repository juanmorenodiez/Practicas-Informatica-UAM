/**
 * @brief It declares the tests for the object module
 *
 * @file object_test.h
 * @author Andrés Mena
 * @version 2.0
 * @date 01-04-2018
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

#include <stdio.h>
#include "types.h"

/*OBJECT SET ORIGINAL POSITION Y OBJECT GET ORIGINAL POSITION*/

/**
 * @test Test object creation
 * @pre object ID
 * @post Non NULL pointer to object
 */
void test1_object_create();

/**
 * @test Test object creation
 * @pre object ID
 * @post Object_ID == Supplied Object Id
 */
void test2_object_create();

/**
 * @test Test obtaining id of object
 * @pre Object pointer NULL
 * @post NO_ID
 */
void test1_object_get_id();

/**
 * @test Test obtaining id of object
 * @pre Object pointer
 * @post id of the object
 */
void test2_object_get_id();

/**
 * @test Test obtaining location of object
 * @pre Object pointer NULL
 * @post NO_ID
 */
void test1_object_get_location();

/**
 * @test Test obtaining location of object
 * @pre Object pointer
 * @post id of object previously added
 */
void test2_object_get_location();

/**
 * @test Test function object_name setting
 * @pre String with space name and Object pointer
 * @post Ouput==OK
 */
void test1_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre Space pointer = NULL
 * @post STATUS=ERROR
 */
void test2_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre NULL string
 * @post STATUS=ERROR
 */
void test3_object_set_name();

/**
 * @test Test function for object_name obtaining
 * @pre Object pointer
 * @post string of characters (previously added)
 */
void test1_object_get_name();

/**
 * @test Test function for object_name obtaining
 * @pre Object pointer NULL
 * @post NULL
 */
void test2_object_get_name();

/**
 * @test Test function for description of object setting
 * @pre String of characters and Object pointer
 * @post STATUS=OK
 */
void test1_object_set_original_description();

/**
 * @test Test function for description of object setting
 * @pre NULL space pointer and string of characters
 * @post STATUS=ERROR
 */
void test2_object_set_original_description();

/**
 * @test Test function for description of object setting
 * @pre String of characters NULL and object pointer
 * @post STATUS=ERROR
 */
void test3_object_set_original_description();

/**
 * @test Test function for description of object obtaining
 * @pre Object pointer
 * @post String with name
 */
void test1_object_get_original_description();

/**
 * @test Test function for description of object obtaining
 * @pre Object pointer NULL
 * @post NULL
 */
void test2_object_get_original_description();

/**
 * @test Test obtaining id of object
 * @pre Object pointer (with object id)
 * @post Id of object
 */
void test1_object_set_id();

/**
 * @test Test obtaining id of object
 * @pre NULL Object pointer
 * @post NULL
 */
void test2_object_set_id();

/**
 * @test Test obtaining location of object
 * @pre Object pointer with object added
 * @post object location == location sent
 */
void test1_object_set_location();

/**
 * @test Test obtaining property movable of object
 * @pre Object pointer
 * @post FALSE property
 */
void test1_object_get_prop_Movable();

/**
 * @test Test obtaining property movable of object
 * @pre NULL Object pointer
 * @post FALSE property
 */
void test2_object_get_prop_Movable();

/**
 * @test Test setting property movable of object
 * @pre Object pointer and TRUE boolean
 * @post TRUE property
 */
void test1_object_set_prop_Movable();

/**
 * @test Test setting property movable of object
 * @pre null Object pointer and FALSE boolean
 * @post FALSE property
 */
void test2_object_set_prop_Movable();

/**
 * @test Test setting property movable of object
 * @pre null Object pointer
 * @post ERROR
 */
void test3_object_set_prop_Movable();

/**
 * @test Test obtaining property moved of object
 * @pre Object pointer
 * @post FALSE property
 */
void test1_object_get_prop_Moved();

/**
 * @test Test obtaining property moved of object
 * @pre NULL Object pointer
 * @post FALSE property
 */
void test2_object_get_prop_Moved();

/**
 * @test Test setting property moved of object
 * @pre Object pointer and TRUE boolean
 * @post TRUE property
 */
void test1_object_set_prop_Moved();

/**
 * @test Test setting property moved of object
 * @pre null Object pointer and FALSE boolean
 * @post FALSE property
 */
void test2_object_set_prop_Moved();

/**
 * @test Test setting property moved of object
 * @pre null Object pointer
 * @post ERROR
 */
void test3_object_set_prop_Moved();

/**
 * @test Test obtaining property illuminate of object
 * @pre Object pointer
 * @post FALSE property
 */
void test1_object_get_prop_Illuminate();

/**
 * @test Test obtaining property illuminate of object
 * @pre NULL Object pointer
 * @post FALSE property
 */
void test2_object_get_prop_Illuminate();

/**
 * @test Test setting property illuminate of object
 * @pre Object pointer and TRUE boolean
 * @post TRUE property
 */
void test1_object_set_prop_Illuminate();

/**
 * @test Test setting property illuminate of object
 * @pre null Object pointer and FALSE boolean
 * @post FALSE property
 */
void test2_object_set_prop_Illuminate();

/**
 * @test Test setting property illuminate of object
 * @pre null Object pointer
 * @post ERROR
 */
void test3_object_set_prop_Illuminate();

/**
 * @test Test obtaining property switchedon of object
 * @pre Object pointer
 * @post FALSE property
 */
void test1_object_get_prop_SwitchedOn();

/**
 * @test Test obtaining property switchedon of object
 * @pre NULL Object pointer
 * @post FALSE property
 */
void test2_object_get_prop_SwitchedOn();

/**
 * @test Test setting property switchedon of object
 * @pre Object pointer and TRUE boolean
 * @post TRUE property
 */
void test1_object_set_prop_SwitchedOn();

/**
 * @test Test setting property switchedon of object
 * @pre null Object pointer and FALSE boolean
 * @post FALSE property
 */
void test2_object_set_prop_SwitchedOn();

/**
 * @test Test setting property switchedon of object
 * @pre null Object pointer
 * @post ERROR
 */
void test3_object_set_prop_SwitchedOn();

/**
 * @test Test getting property open of object
 * @pre Object pointer
 * @post NO_ID
 */
void test1_object_get_prop_Open();

/**
 * @test Test getting property open of object
 * @pre null Object pointer
 * @post NO_ID
 */
void test2_object_get_prop_Open();

/**
 * @test Test setting property open of object
 * @pre Object pointer and ID
 * @post ID previously introduced
 */
void test1_object_set_prop_Open();

/**
 * @test Test setting property open of object
 * @pre Object pointer and NO_ID
 * @post ERROR
 */
void test2_object_set_prop_Open();

/**
 * @test Test setting property open of object
 * @pre null Object pointer
 * @post ERROR
 */
void test3_object_set_prop_Open();

/**
 * @test Test getting original position of object
 * @pre Object pointer
 * @post NO_ID
 */
void test1_object_get_original_position();

/**
 * @test Test getting original position of object
 * @pre NULL Object pointer
 * @post NO_ID
 */
void test2_object_get_original_position();

/**
 * @test Test getting original position of object
 * @pre Object pointer with a position
 * @post Position introduced previously
 */
void test3_object_get_original_position();

/**
 * @test Test setting original position of object
 * @pre Object pointer with a position
 * @post Position introduced previously
 */
void test1_object_set_original_position();

/**
 * @test Test setting original position of object
 * @pre Object pointer with NO_ID
 * @post ERROR
 */
void test2_object_set_original_position();

/**
 * @test Test setting original position of object
 * @pre null Object pointer
 * @post ERROR
 */
void test3_object_set_original_position();

/**
 * @test Test obtaining property Hidden of object
 * @pre Object pointer
 * @post FALSE property
 */
void test1_object_get_prop_Hidden();

/**
 * @test Test obtaining property Hidden of object
 * @pre NULL Object pointer
 * @post FALSE property
 */
void test2_object_get_prop_Hidden();

/**
 * @test Test setting property Hidden of object
 * @pre Object pointer and TRUE boolean
 * @post TRUE property
 */
void test1_object_set_prop_Hidden();

/**
 * @test Test setting property Hidden of object
 * @pre null Object pointer and FALSE boolean
 * @post FALSE property
 */
void test2_object_set_prop_Hidden();

/**
 * @test Test setting property Hidden of object
 * @pre null Object pointer
 * @post ERROR
 */
void test3_object_set_prop_Hidden();

#endif

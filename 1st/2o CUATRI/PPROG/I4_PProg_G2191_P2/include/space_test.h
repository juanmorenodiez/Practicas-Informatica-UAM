/**
 * @brief It declares the tests for the space module
 *
 * @file space_test.h
 * @author Juan Moreno
 * @version 2.0
 * @date 01-04-2018
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

#include <stdio.h>
#include "types.h"

/**
 * @test Test space creation
 * @pre Space ID
 * @post Non NULL pointer to space
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test space destruction
 * @pre NULL pointer to space
 * @post STATUS==ERROR
 */
void test1_space_destroy();

/**
 * @test Test space destruction
 * @pre Space pointer
 * @post STATUS==OK
 */
void test2_space_destroy();

/**
 * @test Test id of space
 * @pre Space pointer NULL
 * @post NO_ID
 */
void test1_space_get_id();

/**
 * @test Test id of space
 * @pre Space pointer not NULL
 * @post Id of the space
 */
void test2_space_get_id();

/**
 * @test Test number of objects in space
 * @pre Space pointer NULL
 * @post NO_ID
 */
void test1_space_get_object_number();

/**
 * @test Test number of objects in space
 * @pre Space without objects pointer
 * @post NO_ID
 */
void test2_space_get_object_number();

/**
 * @test Test number of objects in space
 * @pre Space (with one object) pointer
 * @post Number of objects in the space (1)
 */
void test3_space_get_object_number();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre Space pointer = NULL
 * @post STATUS=ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre NULL string
 * @post STATUS=ERROR
 */
void test3_space_set_name();

/**
 * @test Test function for space_name obtaining
 * @pre Space pointer
 * @post String with name
 */
void test1_space_get_name();

/**
 * @test Test function for space_name obtaining
 * @pre Space pointer NULL
 * @post NULL
 */
void test2_space_get_name();

/**
 * @test Test function for description of space setting
 * @pre String of characters
 * @post STATUS=OK
 */
void test1_space_set_short_description();

/**
 * @test Test function for description of space setting
 * @pre NULL space pointer
 * @post STATUS=ERROR
 */
void test2_space_set_short_description();

/**
 * @test Test function for description of space setting
 * @pre String of characters NULL
 * @post STATUS=ERROR
 */
void test3_space_set_short_description();

/**
 * @test Test function for description of space obtaining
 * @pre Space pointer
 * @post String with name
 */
void test1_space_get_short_description();

/**
 * @test Test function for description of space obtaining
 * @pre Space pointer NULL
 * @post NULL
 */
void test2_space_get_short_description();

/**
 * @test Test function for description of space setting
 * @pre String of characters
 * @post STATUS=OK
 */
void test1_space_set_long_description();

/**
 * @test Test function for description of space setting
 * @pre NULL space pointer
 * @post STATUS=ERROR
 */
void test2_space_set_long_description();

/**
 * @test Test function for description of space setting
 * @pre String of characters NULL
 * @post STATUS=ERROR
 */
void test3_space_set_long_description();

/**
 * @test Test function for description of space obtaining
 * @pre Space pointer
 * @post String with name
 */
void test1_space_get_long_description();

/**
 * @test Test function for description of space obtaining
 * @pre Space pointer NULL
 * @post NULL
 */
void test2_space_get_long_description();

/**
 * @test Test function for setting objects
 * @pre Space pointer NULL and object pointer
 * @post ERROR
 */
void test1_space_set_object();

/**
 * @test Test function for setting objects
 * @pre Space pointer and object pointer
 * @post OK
 */
void test2_space_set_object();

/**
 * @test Test function for getting objects
 * @pre Space pointer and object pointer
 * @post Not NULL
 */
void test1_space_get_object();

/**
 * @test Test function for setting north space
 * @pre Space pointer NULL
 * @post ERROR
 */
void test1_space_set_north();

/**
 * @test Test function for setting north space
 * @pre Space pointer and NO_ID
 * @post ERROR
 */
void test2_space_set_north();

/**
 * @test Test function for setting north space
 * @pre Space pointer and id
 * @post OK
 */
void test3_space_set_north();

/**
 * @test Test function for getting north space
 * @pre Space pointer NULL
 * @post NO_ID
 */
void test1_space_get_north();

/**
 * @test Test function for getting north space
 * @pre Space pointer
 * @post ID of north space
 */
void test2_space_get_north();

/**
* @test Test function for setting south space
* @pre Space pointer NULL
* @post ERROR
*/
void test1_space_set_south();

/**
* @test Test function for setting south space
* @pre Space pointer and NO_ID
* @post ERROR
*/
void test2_space_set_south();

/**
* @test Test function for setting south space
* @pre Space pointer and id
* @post OK
*/
void test3_space_set_south();

/**
* @test Test function for getting south space
* @pre Space pointer NULL
* @post NO_ID
*/
void test1_space_get_south();

/**
* @test Test function for getting south space
* @pre Space pointer
* @post ID of south space
*/
void test2_space_get_south();

/**
* @test Test function for setting east space
* @pre Space pointer NULL
* @post ERROR
*/
void test1_space_set_east();

/**
* @test Test function for setting east space
* @pre Space pointer and NO_ID
* @post ERROR
*/
void test2_space_set_east();

/**
* @test Test function for setting east space
* @pre Space pointer and id
* @post OK
*/
void test3_space_set_east();

/**
* @test Test function for getting east space
* @pre Space pointer NULL
* @post NO_ID
*/
void test1_space_get_east();

/**
* @test Test function for getting east space
* @pre Space pointer
* @post ID of east space
*/
void test2_space_get_east();

/**
* @test Test function for setting west space
* @pre Space pointer NULL
* @post ERROR
*/
void test1_space_set_west();

/**
* @test Test function for setting west space
* @pre Space pointer and NO_ID
* @post ERROR
*/
void test2_space_set_west();

/**
* @test Test function for setting west space
* @pre Space pointer and id
* @post OK
*/
void test3_space_set_west();

/**
* @test Test function for getting west space
* @pre Space pointer NULL
* @post NO_ID
*/
void test1_space_get_west();

/**
* @test Test function for getting west space
* @pre Space pointer
* @post ID of west space
*/
void test2_space_get_west();

/**
* @test Test function for getting iluminate property of space
* @pre Space pointer
* @post FALSE
*/
void test1_space_get_iluminate();

/**
* @test Test function for getting iluminate property of space
* @pre null Space pointer
* @post FALSE
*/
void test2_space_get_iluminate();

/**
* @test Test function for setting iluminate property of space
* @pre Space pointer and FALSE
* @post FALSE
*/
void test1_space_set_iluminate();

/**
* @test Test function for setting iluminate property of space
* @pre null Space pointer and TRUE
* @post TRUE
*/
void test2_space_set_iluminate();

/**
* @test Test function for setting up space
* @pre Space pointer NULL
* @post ERROR
*/
void test1_space_set_up();

/**
* @test Test function for setting up space
* @pre Space pointer and NO_ID
* @post ERROR
*/
void test2_space_set_up();

/**
* @test Test function for setting up space
* @pre Space pointer and id
* @post OK
*/
void test3_space_set_up();

/**
* @test Test function for getting up space
* @pre Space pointer NULL
* @post NO_ID
*/
void test1_space_get_up();

/**
* @test Test function for getting up space
* @pre Space pointer
* @post ID of up space
*/
void test2_space_get_up();

/**
* @test Test function for setting down space
* @pre Space pointer NULL
* @post ERROR
*/
void test1_space_set_down();

/**
* @test Test function for setting down space
* @pre Space pointer and NO_ID
* @post ERROR
*/
void test2_space_set_down();

/**
* @test Test function for setting down space
* @pre Space pointer and id
* @post OK
*/
void test3_space_set_down();

/**
* @test Test function for getting down space
* @pre Space pointer NULL
* @post NO_ID
*/
void test1_space_get_down();

/**
* @test Test function for getting down space
* @pre Space pointer
* @post ID of down space
*/
void test2_space_get_down();

#endif

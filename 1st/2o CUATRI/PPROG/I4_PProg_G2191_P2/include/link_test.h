/**
 * @brief It declares the tests for the link module
 *
 * @file link_test.h
 * @author Andres Mena Godino
 * @version 2.0
 * @date 01-03-2018
 * @copyright GNU Public License
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Test link creation
 * @pre NO_ID
 * @post NULL pointer to link
 */
void test1_link_create();

/**
 * @test Test link creation
 * @pre ID
 * @post link ID == id introduced
 */
void test2_link_create();

/**
 * @test Test function for link_name setting
 * @pre pointer to link and string with link name
 * @post Ouput==OK
 */
void test1_link_set_name();

/**
 * @test Test function for link_name setting
 * @pre NULL pointer to link and string with link name
 * @post Ouput==ERROR
 */
void test2_link_set_name();

/**
 * @test Test function for link_name setting
 * @pre pointer to link and NULL string of characters
 * @post Ouput==ERROR
 */
void test3_link_set_name();

/**
 * @test Test function for setting first link
 * @pre pointer to link and id
 * @post Ouput==OK
 */
void test1_link_set_link1();

/**
 * @test Test function for setting first link
 * @pre NULL pointer to link and id
 * @post Ouput==ERROR
 */
void test2_link_set_link1();

/**
 * @test Test function for setting second link
 * @pre pointer to link and id
 * @post Ouput==OK
 */
void test1_link_set_link2();

/**
 * @test Test function for setting second link
 * @pre NULL pointer to link and id
 * @post Ouput==ERROR
 */
void test2_link_set_link2();

/**
 * @test Test function for setting status of link
 * @pre Pointer to link and LINK_ST
 * @post Ouput==OK
 */
void test1_link_set_status();

/**
 * @test Test function for setting status of link
 * @pre NULL pointer to link and LINK_ST
 * @post Ouput==ERROR
 */
void test2_link_set_status();

/**
 * @test Test function for link_name obtaining
 * @pre Link pointer
 * @post String with name
 */
void test1_link_get_name();

/**
 * @test Test function for link_name obtaining
 * @pre NULL link pointer
 * @post NULL string
 */
void test2_link_get_name();

/**
 * @test Test function for getting first link
 * @pre Link pointer (with first link created)
 * @post id of first link
 */
void test1_link_get_link1();

/**
 * @test Test function for getting first link
 * @pre NULL link pointer
 * @post NO_ID
 */
void test2_link_get_link1();

/**
 * @test Test function for getting second link
 * @pre Link pointer (with second link created)
 * @post id of second link
 */
void test1_link_get_link2();

/**
 * @test Test function for getting second link
 * @pre NULL link pointer
 * @post NO_ID
 */
void test2_link_get_link2();

/**
 * @test Test function for getting link id
 * @pre Pointer to link
 * @post link_ID == Supplied link Id
 */
void test1_link_get_id();

/**
 * @test Test function for getting link id
 * @pre NULL pointer to link
 * @post NO_ID
 */
void test2_link_get_id();

/**
 * @test Test function for destroying link
 * @pre NULL pointer to link
 * @post ERROR
 */
void test1_link_destroy();

/**
 * @test Test function for destroying link
 * @pre pointer to link
 * @post OK
 */
void test2_link_destroy();

/**
 * @test Test function for printing link
 * @pre NULL pointer to link
 * @post ERROR
 */
void test1_link_print();

/**
 * @test Test function for setting link key
 * @pre NULL pointer to link
 * @post ERROR
 */
void test1_link_set_key();

/**
 * @test Test function for setting link key
 * @pre Pointer to link and NO_ID
 * @post ERROR
 */
void test2_link_set_key();

/**
 * @test Test function for setting link key
 * @pre Pointer to link and ID
 * @post OK
 */
void test3_link_set_key();

/**
 * @test Test function for getting link key
 * @pre null Pointer to link
 * @post NO_ID
 */
void test1_link_get_key();

/**
 * @test Test function for getting link key
 * @pre Pointer to link
 * @post Zero
 */
void test2_link_get_key();

/**
 * @test Test function for getting link key
 * @pre Pointer to link and introduced id
 * @post Id previosuly introduced
 */
void test3_link_get_key();


#endif

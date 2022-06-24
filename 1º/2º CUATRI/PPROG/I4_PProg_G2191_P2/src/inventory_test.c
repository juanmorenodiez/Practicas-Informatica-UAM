/**
 * @brief It tests inventory module
 *
 * @file inventory_test.c
 * @author Andres Mena
 * @version 1.0
 * @date 31-03-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "inventory_test.h"
#include "test.h"
#include "set.h"

#define MAX_TESTS 21  /*!< Max amount of tests posible */

/**
 * @brief Main function for inventory unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */

int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module player:\n");
  }
  else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
  	if (test < 1 && test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
  	  exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_inventory_create();
  if (all || test == 2) test1_inventory_add_id();
  if (all || test == 3) test2_inventory_add_id();
  if (all || test == 4) test3_inventory_add_id();
  if (all || test == 5) test4_inventory_add_id();
  if (all || test == 6) test5_inventory_add_id();
  if (all || test == 7) test1_inventory_get_set();
  if (all || test == 8) test2_inventory_get_set();
  if (all || test == 9) test1_inventory_delete_id();
  if (all || test == 10) test2_inventory_delete_id();
  if (all || test == 11) test3_inventory_delete_id();
  if (all || test == 12) test1_inventory_destroy();
  if (all || test == 13) test2_inventory_destroy();
  if (all || test == 14) test1_inventory_print();
  if (all || test == 15) test1_inventory_is_full();
  if (all || test == 16) test2_inventory_is_full();
  if (all || test == 17) test1_inventory_is_empty();
  if (all || test == 18) test2_inventory_is_empty();
  if (all || test == 19) test3_inventory_is_empty();
  if (all || test == 20) test1_inventory_get_object();
  if (all || test == 21) test2_inventory_get_object();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

 void test1_inventory_create() {
   Inventory *i=NULL;
   i=inventory_create();
   PRINT_TEST_RESULT(i!=NULL);
   inventory_destroy(i);
 }

 void test1_inventory_add_id() {
     Inventory *i = NULL;
     PRINT_TEST_RESULT(inventory_add_id(i, NO_ID) == ERROR);
 }

 void test2_inventory_add_id() {
     Inventory *i = NULL;
     PRINT_TEST_RESULT(inventory_add_id(i, 3) == ERROR);
 }

 void test3_inventory_add_id() {
     Inventory *i = NULL;
     i=inventory_create();
     PRINT_TEST_RESULT(inventory_add_id(i, NO_ID) == ERROR);
     inventory_destroy(i);
 }

 void test4_inventory_add_id() {
     Inventory *i = NULL;
     i=inventory_create();
     PRINT_TEST_RESULT(inventory_add_id(i, 5) == OK);
     inventory_destroy(i);
 }

 void test5_inventory_add_id() {
     Inventory *i = NULL;
     int j=0;

     i=inventory_create();
     for (j=0; j<4; j++){
       inventory_add_id(i, j);
     }
     PRINT_TEST_RESULT(inventory_add_id(i, 5) == ERROR);
     inventory_destroy(i);
 }


 void test1_inventory_get_set() {
     Inventory *i = NULL;
     Set *s=NULL;

     s=inventory_get_set(i);
     PRINT_TEST_RESULT(s == NULL);
 }

 void test2_inventory_get_set() {
     Inventory *i = NULL;
     Set *s=NULL;

     i=inventory_create();
     inventory_add_id(i, 3);
     s=inventory_get_set(i);
     PRINT_TEST_RESULT(s != NULL);
     inventory_destroy(i);
 }

 void test1_inventory_delete_id() {
     Inventory *i = NULL;
     PRINT_TEST_RESULT(inventory_delete_id(i, NO_ID) == ERROR);
 }

 void test2_inventory_delete_id() {
     Inventory *i = NULL;
     PRINT_TEST_RESULT(inventory_delete_id(i, 3) == ERROR);
 }

 void test3_inventory_delete_id() {
     Inventory *i = NULL;
     i=inventory_create();
     inventory_add_id(i, 3);
     PRINT_TEST_RESULT(inventory_delete_id(i, 3) == OK);
     inventory_destroy(i);
 }

 void test1_inventory_destroy() {
   Inventory *i = NULL;
   PRINT_TEST_RESULT(inventory_destroy(i) == ERROR);
 }

 void test2_inventory_destroy() {
   Inventory *i = NULL;
   i=inventory_create();
   PRINT_TEST_RESULT(inventory_destroy(i) == OK);
 }

 void test1_inventory_print() {
   Inventory *i = NULL;
   PRINT_TEST_RESULT(inventory_print(i) == ERROR);
 }

 void test1_inventory_get_object(){
    Inventory *i=NULL;
    PRINT_TEST_RESULT(inventory_get_object(i, 0) == NO_ID);
}

void test2_inventory_get_object(){
    Inventory *i=NULL;
    i=inventory_create(1);
    inventory_add_id(i, 8);
    PRINT_TEST_RESULT(inventory_get_object(i, 0) == 8);
    inventory_destroy(i);
}

void test1_inventory_is_empty(){
    Inventory *i=NULL;
    PRINT_TEST_RESULT(inventory_is_empty(i) == FALSE);
}

void test2_inventory_is_empty(){
    Inventory *i=NULL;
    i=inventory_create(5);
    PRINT_TEST_RESULT(inventory_is_empty(i) == TRUE);
    inventory_destroy(i);
}

void test3_inventory_is_empty(){
    Inventory *i=NULL;
    i=inventory_create(5);
    inventory_add_id(i, 6);
    PRINT_TEST_RESULT(inventory_is_empty(i) == FALSE);
    inventory_destroy(i);
}

void test1_inventory_is_full(){
    Inventory *i=NULL;
    PRINT_TEST_RESULT(inventory_is_full(i) == FALSE);
}

void test2_inventory_is_full(){
    Inventory *i=NULL;
    i=inventory_create(1);
    PRINT_TEST_RESULT(inventory_is_full(i) == FALSE);
    inventory_destroy(i);
}

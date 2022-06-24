/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @author Andres Mena
 * @version 1.0
 * @date 31-03-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"
#include "inventory.h"
#include "object.h"


#define MAX_TESTS 55  /*!< Max amount of tests posible */

/**
 * @brief Main function for object unit tests.
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


  if (all || test == 1) test1_object_create();
  if (all || test == 2) test2_object_create();
  if (all || test == 3) test1_object_get_id();
  if (all || test == 4) test2_object_get_id();
  if (all || test == 5) test1_object_get_location();
  if (all || test == 6) test2_object_get_location();
  if (all || test == 7) test1_object_set_name();
  if (all || test == 8) test2_object_set_name();
  if (all || test == 9) test3_object_set_name();
  if (all || test == 10) test1_object_get_name();
  if (all || test == 11) test2_object_get_name();
  if (all || test == 12) test1_object_set_original_description();
  if (all || test == 13) test2_object_set_original_description();
  if (all || test == 14) test3_object_set_original_description();
  if (all || test == 15) test1_object_get_original_description();
  if (all || test == 16) test2_object_get_original_description();
  if (all || test == 17) test1_object_set_id();
  if (all || test == 18) test2_object_set_id();
  if (all || test == 19) test1_object_set_location();
  if (all || test == 20) test1_object_get_prop_Movable();
  if (all || test == 21) test2_object_get_prop_Movable();
  if (all || test == 22) test1_object_set_prop_Movable();
  if (all || test == 23) test2_object_set_prop_Movable();
  if (all || test == 24) test3_object_set_prop_Movable();
  if (all || test == 25) test1_object_get_prop_Moved();
  if (all || test == 26) test2_object_get_prop_Moved();
  if (all || test == 27) test1_object_set_prop_Moved();
  if (all || test == 28) test2_object_set_prop_Moved();
  if (all || test == 29) test3_object_set_prop_Moved();
  if (all || test == 30) test1_object_get_prop_Illuminate();
  if (all || test == 31) test2_object_get_prop_Illuminate();
  if (all || test == 32) test1_object_set_prop_Illuminate();
  if (all || test == 33) test2_object_set_prop_Illuminate();
  if (all || test == 34) test3_object_set_prop_Illuminate();
  if (all || test == 35) test1_object_get_prop_SwitchedOn();
  if (all || test == 36) test2_object_get_prop_SwitchedOn();
  if (all || test == 37) test1_object_set_prop_SwitchedOn();
  if (all || test == 38) test2_object_set_prop_SwitchedOn();
  if (all || test == 39) test3_object_set_prop_SwitchedOn();
  if (all || test == 40) test1_object_get_prop_Open();
  if (all || test == 41) test2_object_get_prop_Open();
  if (all || test == 42) test1_object_set_prop_Open();
  if (all || test == 43) test2_object_set_prop_Open();
  if (all || test == 44) test3_object_set_prop_Open();
  if (all || test == 45) test1_object_get_original_position();
  if (all || test == 46) test2_object_get_original_position();
  if (all || test == 47) test3_object_get_original_position();
  if (all || test == 48) test1_object_set_original_position();
  if (all || test == 49) test2_object_set_original_position();
  if (all || test == 50) test3_object_set_original_position();
  if (all || test == 51) test1_object_get_prop_Hidden();
  if (all || test == 52) test2_object_get_prop_Hidden();
  if (all || test == 53) test1_object_set_prop_Hidden();
  if (all || test == 54) test2_object_set_prop_Hidden();
  if (all || test == 55) test3_object_set_prop_Hidden();



  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_object_create() {
  Object *o=NULL;
  o=object_create(1);
  PRINT_TEST_RESULT(o!=NULL);
  object_destroy(o);
  }

void test2_object_create() {
  Object *o=NULL;
  o=object_create(4);
  PRINT_TEST_RESULT(object_get_id(o)==4);
  object_destroy(o);
  }

void test1_object_get_id() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_get_id(o)==NO_ID);
  }

void test2_object_get_id() {
  Object *o=NULL;
  o=object_create(9);
  PRINT_TEST_RESULT(object_get_id(o)==9);
  object_destroy(o);
  }

void test1_object_get_location() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_get_id(o)==NO_ID);
  }

void test2_object_get_location() {
  Object *o=NULL;
  o=object_create(5);
  object_set_location(o, 15);
  PRINT_TEST_RESULT(object_get_location(o)==15);
  object_destroy(o);
  }

void test1_object_set_name() {
  Object *o = NULL;
  o = object_create(1);
  PRINT_TEST_RESULT(object_set_name(o, "test") == OK);
  object_destroy(o);
  }

void test2_object_set_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_name(o, "test") == ERROR);
  }

void test3_object_set_name() {
  Object *o = NULL;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_name(o, NULL) == ERROR);
  object_destroy(o);
  }

void test1_object_get_name() {
  Object *o = NULL;
  o = object_create(1);
  object_set_name(o, "hello");
  PRINT_TEST_RESULT(strcmp(object_get_name(o), "hello") == 0);
  object_destroy(o);
  }

void test2_object_get_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_name(o) == NULL);
  }

void test1_object_set_original_description() {
  Object *o = NULL;
  o = object_create(1);
  PRINT_TEST_RESULT(object_set_original_description(o, "stick") == OK);
  object_destroy(o);
  }

void test2_object_set_original_description() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_original_description(o, "stick") == ERROR);
  }

void test3_object_set_original_description() {
  Object *o = NULL;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_original_description(o, NULL) == ERROR);
  object_destroy(o);
  }

void test1_object_get_original_description() {
  Object *o = NULL;
  o = object_create(1);
  object_set_original_description(o, "stone");
  PRINT_TEST_RESULT(strcmp(object_get_original_description(o), "stone") == 0);
  object_destroy(o);
  }

void test2_object_get_original_description() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_original_description(o) == NULL);
  }

void test1_object_set_id() {
  Object *o=NULL;
  o=object_create(1);
  object_set_id(o, 5);
  PRINT_TEST_RESULT(object_get_id(o)==5);
  object_destroy(o);
  }

void test2_object_set_id() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_set_id(o, 3)==ERROR);
  }

void test1_object_set_location() {
  Object *o=NULL;
  o=object_create(3);
  object_set_location(o, 8);
  PRINT_TEST_RESULT(object_get_location(o)==8);
  object_destroy(o);
  }

void test1_object_get_prop_Movable() {
  Object *o=NULL;
  o=object_create(1);
  PRINT_TEST_RESULT(object_get_prop_Movable(o)==FALSE);
  object_destroy(o);
  }

void test2_object_get_prop_Movable() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_get_prop_Movable(o)==FALSE);
  }

void test1_object_set_prop_Movable() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_Movable(o, TRUE);
  PRINT_TEST_RESULT(object_get_prop_Movable(o)==TRUE);
  object_destroy(o);
  }

void test2_object_set_prop_Movable() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_Movable(o, FALSE);
  PRINT_TEST_RESULT(object_get_prop_Movable(o)==FALSE);
  object_destroy(o);
  }

void test3_object_set_prop_Movable() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_set_prop_Movable(o, TRUE)==ERROR);
  }

void test1_object_get_prop_Moved() {
  Object *o=NULL;
  o=object_create(1);
  PRINT_TEST_RESULT(object_get_prop_Moved(o)==FALSE);
  object_destroy(o);
  }

void test2_object_get_prop_Moved() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_get_prop_Moved(o)==FALSE);
  }

void test1_object_set_prop_Moved() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_Moved(o, TRUE);
  PRINT_TEST_RESULT(object_get_prop_Moved(o)==TRUE);
  object_destroy(o);
  }

void test2_object_set_prop_Moved() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_Moved(o, FALSE);
  PRINT_TEST_RESULT(object_get_prop_Moved(o)==FALSE);
  object_destroy(o);
  }

void test3_object_set_prop_Moved() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_set_prop_Moved(o, TRUE)==ERROR);
  }

void test1_object_get_prop_Hidden() {
  Object *o=NULL;
  o=object_create(1);
  PRINT_TEST_RESULT(object_get_prop_Hidden(o)==FALSE);
  object_destroy(o);
  }

void test2_object_get_prop_Hidden() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_get_prop_Hidden(o)==FALSE);
  }

void test1_object_set_prop_Hidden() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_Hidden(o, TRUE);
  PRINT_TEST_RESULT(object_get_prop_Hidden(o)==TRUE);
  object_destroy(o);
  }

void test2_object_set_prop_Hidden() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_Hidden(o, FALSE);
  PRINT_TEST_RESULT(object_get_prop_Hidden(o)==FALSE);
  object_destroy(o);
  }

void test3_object_set_prop_Hidden() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_set_prop_Hidden(o, TRUE)==ERROR);
  }

void test1_object_get_prop_Illuminate() {
  Object *o=NULL;
  o=object_create(1);
  PRINT_TEST_RESULT(object_get_prop_Illuminate(o)==FALSE);
  object_destroy(o);
  }

void test2_object_get_prop_Illuminate() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_get_prop_Illuminate(o)==FALSE);
  }

void test1_object_set_prop_Illuminate() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_Illuminate(o, TRUE);
  PRINT_TEST_RESULT(object_get_prop_Illuminate(o)==TRUE);
  object_destroy(o);
  }

void test2_object_set_prop_Illuminate() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_Illuminate(o, FALSE);
  PRINT_TEST_RESULT(object_get_prop_Illuminate(o)==FALSE);
  object_destroy(o);
  }

void test3_object_set_prop_Illuminate() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_set_prop_Illuminate(o, TRUE)==ERROR);
  }

void test1_object_get_prop_SwitchedOn() {
  Object *o=NULL;
  o=object_create(1);
  PRINT_TEST_RESULT(object_get_prop_SwitchedOn(o)==FALSE);
  object_destroy(o);
  }

void test2_object_get_prop_SwitchedOn() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_get_prop_SwitchedOn(o)==FALSE);
  }

void test1_object_set_prop_SwitchedOn() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_SwitchedOn(o, TRUE);
  PRINT_TEST_RESULT(object_get_prop_SwitchedOn(o)==TRUE);
  object_destroy(o);
  }

void test2_object_set_prop_SwitchedOn() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_SwitchedOn(o, FALSE);
  PRINT_TEST_RESULT(object_get_prop_SwitchedOn(o)==FALSE);
  object_destroy(o);
  }

void test3_object_set_prop_SwitchedOn() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_set_prop_SwitchedOn(o, TRUE)==ERROR);
  }

void test1_object_get_prop_Open() {
  Object *o=NULL;
  o=object_create(1);
  PRINT_TEST_RESULT(object_get_prop_Open(o)==NO_ID);
  object_destroy(o);
  }

void test2_object_get_prop_Open() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_get_prop_Open(o)==NO_ID);
  }

void test1_object_set_prop_Open() {
  Object *o=NULL;
  o=object_create(1);
  object_set_prop_Open(o, 5);
  PRINT_TEST_RESULT(object_get_prop_Open(o)==5);
  object_destroy(o);
  }

void test2_object_set_prop_Open() {
  Object *o=NULL;
  o=object_create(1);
  PRINT_TEST_RESULT(object_set_prop_Open(o, -1)==ERROR);
  object_destroy(o);
  }

void test3_object_set_prop_Open() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_set_prop_Open(o, -1)==ERROR);
  }

void test1_object_get_original_position() {
  Object *o=NULL;
  o=object_create(1);
  PRINT_TEST_RESULT(object_get_original_position(o)==NO_ID);
  object_destroy(o);
  }

void test2_object_get_original_position() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_get_original_position(o)==NO_ID);
  }

void test3_object_get_original_position() {
  Object *o=NULL;
  o=object_create(1);
  object_set_original_position(o, 5);
  PRINT_TEST_RESULT(object_get_original_position(o)==5);
  object_destroy(o);
  }

void test1_object_set_original_position() {
  Object *o=NULL;
  o=object_create(1);
  object_set_original_position(o, 5);
  PRINT_TEST_RESULT(object_get_original_position(o)==5);
  object_destroy(o);
  }

void test2_object_set_original_position() {
  Object *o=NULL;
  o=object_create(1);
  PRINT_TEST_RESULT(object_set_original_position(o, -1)==ERROR);
  object_destroy(o);
  }

void test3_object_set_original_position() {
  Object *o=NULL;
  PRINT_TEST_RESULT(object_set_original_position(o, 1)==ERROR);
  }

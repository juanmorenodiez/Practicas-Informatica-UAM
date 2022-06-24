/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Andres Mena
 * @version 1.0
 * @date 31-03-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "space_test.h"
#include "test.h"
#include "inventory.h"
#include "space.h"


#define MAX_TESTS 61 /*!< Max amount of tests posible */

/**
 * @brief Main function for space unit tests.
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


  if (all || test == 1) test1_space_create();
  if (all || test == 2) test2_space_create();
  if (all || test == 3) test1_space_destroy();
  if (all || test == 4) test2_space_destroy();
  if (all || test == 5) test1_space_get_id();
  if (all || test == 6) test2_space_get_id();
  if (all || test == 7) test1_space_get_object_number();
  if (all || test == 8) test2_space_get_object_number();
  if (all || test == 9) test3_space_get_object_number();
  if (all || test == 10) test1_space_set_name();
  if (all || test == 11) test2_space_set_name();
  if (all || test == 12) test3_space_set_name();
  if (all || test == 13) test1_space_get_name();
  if (all || test == 14) test2_space_get_name();
  if (all || test == 15) test1_space_set_short_description();
  if (all || test == 16) test2_space_set_short_description();
  if (all || test == 17) test3_space_set_short_description();
  if (all || test == 18) test1_space_get_short_description();
  if (all || test == 19) test2_space_get_short_description();
  if (all || test == 20) test1_space_set_object();
  if (all || test == 21) test2_space_set_object();
  if (all || test == 22) test1_space_get_object();
  if (all || test == 23) test1_space_set_north();
  if (all || test == 24) test2_space_set_north();
  if (all || test == 25) test3_space_set_north();
  if (all || test == 26) test1_space_get_north();
  if (all || test == 27) test2_space_get_north();
  if (all || test == 28) test1_space_set_south();
  if (all || test == 29) test2_space_set_south();
  if (all || test == 30) test3_space_set_south();
  if (all || test == 31) test1_space_get_south();
  if (all || test == 32) test2_space_get_south();
  if (all || test == 33) test1_space_set_east();
  if (all || test == 34) test2_space_set_east();
  if (all || test == 35) test3_space_set_east();
  if (all || test == 36) test1_space_get_east();
  if (all || test == 37) test2_space_get_east();
  if (all || test == 38) test1_space_set_west();
  if (all || test == 39) test2_space_set_west();
  if (all || test == 40) test3_space_set_west();
  if (all || test == 41) test1_space_get_west();
  if (all || test == 42) test2_space_get_west();
  if (all || test == 43) test1_space_set_long_description();
  if (all || test == 44) test2_space_set_long_description();
  if (all || test == 45) test3_space_set_long_description();
  if (all || test == 46) test1_space_get_long_description();
  if (all || test == 47) test2_space_get_long_description();
  if (all || test == 48) test1_space_get_iluminate();
  if (all || test == 49) test2_space_get_iluminate();
  if (all || test == 50) test1_space_set_iluminate();
  if (all || test == 51) test2_space_set_iluminate();
  if (all || test == 52) test1_space_set_up();
  if (all || test == 53) test2_space_set_up();
  if (all || test == 54) test3_space_set_up();
  if (all || test == 55) test1_space_get_up();
  if (all || test == 56) test2_space_get_up();
  if (all || test == 57) test1_space_set_down();
  if (all || test == 58) test2_space_set_down();
  if (all || test == 59) test3_space_set_down();
  if (all || test == 60) test1_space_get_down();
  if (all || test == 61) test2_space_get_down();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_space_create() {
  Space *s=NULL;
  s=space_create(1);
  PRINT_TEST_RESULT(s!=NULL);
  space_destroy(s);
  }

void test2_space_create() {
  Space *s=NULL;
  s=space_create(4);
  PRINT_TEST_RESULT(space_get_id(s)==4);
  space_destroy(s);
  }

void test1_space_destroy() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_destroy(s) == ERROR);
  }

void test2_space_destroy() {
  Space *s = NULL;
  s=space_create(2);
  PRINT_TEST_RESULT(space_destroy(s) == OK);
  }

void test1_space_set_name() {
  Space *s = NULL;
  s = space_create(1);
  PRINT_TEST_RESULT(space_set_name(s, "test") == OK);
  space_destroy(s);
  }

void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "test") == ERROR);
  }

void test3_space_set_name() {
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
  }

void test1_space_get_name() {
  Space *s = NULL;
  s = space_create(1);
  space_set_name(s, "hello");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "hello") == 0);
  space_destroy(s);
  }

void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
  }

void test1_space_set_short_description() {
  Space *s = NULL;
  s = space_create(1);
  PRINT_TEST_RESULT(space_set_short_description(s, "test") == OK);
  space_destroy(s);
  }

void test2_space_set_short_description() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_short_description(s, "test") == ERROR);
  }

void test3_space_set_short_description() {
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_short_description(s, NULL) == ERROR);
  space_destroy(s);
  }

void test1_space_get_short_description() {
  Space *s = NULL;
  s = space_create(1);
  space_set_short_description(s, "test");
  PRINT_TEST_RESULT(strcmp(space_get_short_description(s), "test") == 0);
  space_destroy(s);
  }

void test2_space_get_short_description() {
  Space *o = NULL;
  PRINT_TEST_RESULT(space_get_short_description(o) == NULL);
  }

void test1_space_set_north() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_set_north(s, 3)==ERROR);
  }

void test2_space_set_north() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_north(s, -1)==ERROR);
  space_destroy(s);
  }

void test3_space_set_north() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_north(s, 1)==OK);
  space_destroy(s);
  }

void test1_space_get_north() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_get_north(s)==NO_ID);
  }

void test2_space_get_north() {
  Space *s=NULL;
  s=space_create(2);
  space_set_north(s, 5);
  PRINT_TEST_RESULT(space_get_north(s)==5);
  space_destroy(s);
  }

void test1_space_set_east() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_set_east(s, 3)==ERROR);
  }

void test2_space_set_east() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_east(s, -1)==ERROR);
  space_destroy(s);
  }

void test3_space_set_east() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_east(s, 1)==OK);
  space_destroy(s);
  }

void test1_space_get_east() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_get_east(s)==NO_ID);
  }

void test2_space_get_east() {
  Space *s=NULL;
  s=space_create(2);
  space_set_east(s, 5);
  PRINT_TEST_RESULT(space_get_east(s)==5);
  space_destroy(s);
  }

void test1_space_set_west() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_set_west(s, 4)==ERROR);
  }

void test2_space_set_west() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_west(s, -1)==ERROR);
  space_destroy(s);
  }

void test3_space_set_west() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_west(s, 1)==OK);
  space_destroy(s);
  }

void test1_space_get_west() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_get_west(s)==NO_ID);
  }

void test2_space_get_west() {
  Space *s=NULL;
  s=space_create(2);
  space_set_west(s, 5);
  PRINT_TEST_RESULT(space_get_west(s)==5);
  space_destroy(s);
  }

void test1_space_set_south() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_set_south(s, 3)==ERROR);
  }

void test2_space_set_south() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_south(s, -1)==ERROR);
  space_destroy(s);
  }

void test3_space_set_south() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_south(s, 1)==OK);
  space_destroy(s);
  }

void test1_space_get_south() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_get_south(s)==NO_ID);
  }

void test2_space_get_south() {
  Space *s=NULL;
  s=space_create(2);
  space_set_south(s, 5);
  PRINT_TEST_RESULT(space_get_south(s)==5);
  space_destroy(s);
  }

void test1_space_set_object() {
  Space *s=NULL;
  Object *o=NULL;
  o=object_create(4);
  PRINT_TEST_RESULT(space_set_object(s, o)==ERROR);
  object_destroy(o);
  }

void test2_space_set_object() {
  Space *s=NULL;
  Object *o=NULL;
  s=space_create(1);
  o=object_create(4);
  PRINT_TEST_RESULT(space_set_object(s, o)==OK);
  object_destroy(o);
  space_destroy(s);
  }

void test1_space_get_object() {
  Space *s=NULL;
  Object *o=NULL;
  Set *a=NULL;
  o=object_create(4);
  s=space_create(2);
  space_set_object(s, o);
  a=space_get_object(s);
  PRINT_TEST_RESULT(a!=NULL);
  space_destroy(s);
  object_destroy(o);
  }

void test1_space_get_id() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_get_id(s)==NO_ID);
  }

void test2_space_get_id() {
  Space *s=NULL;
  s=space_create(8);
  PRINT_TEST_RESULT(space_get_id(s)==8);
  space_destroy(s);
  }

void test1_space_get_object_number() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_get_object_number(s)==-1);
  }

void test2_space_get_object_number() {
  Space *s=NULL;
  s=space_create(1);
  PRINT_TEST_RESULT(space_get_object_number(s)==-1);
  space_destroy(s);
  }

void test3_space_get_object_number() {
  Space *s=NULL;
  Object *o=NULL;
  s=space_create(1);
  o=object_create(2);
  space_set_object(s, o);
  PRINT_TEST_RESULT(space_get_object_number(s)==0);
  space_destroy(s);
  object_destroy(o);
}

void test1_space_set_long_description() {
  Space *s = NULL;
  s = space_create(1);
  PRINT_TEST_RESULT(space_set_long_description(s, "test") == OK);
  space_destroy(s);
}

void test2_space_set_long_description() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_long_description(s, "test") == ERROR);
}

void test3_space_set_long_description() {
  Space *s = NULL;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_long_description(s, NULL) == ERROR);
  space_destroy(s);
}

void test1_space_get_long_description() {
  Space *s = NULL;
  s = space_create(1);
  space_set_long_description(s, "test");
  PRINT_TEST_RESULT(strcmp(space_get_long_description(s), "test") == 0);
  space_destroy(s);
}

void test2_space_get_long_description() {
  Space *o = NULL;
  PRINT_TEST_RESULT(space_get_long_description(o) == NULL);
}

void test1_space_get_iluminate() {
  Space *s=NULL;
  s=space_create(1);
  PRINT_TEST_RESULT(space_get_iluminate(s)==FALSE);
  space_destroy(s);
  }

void test2_space_get_iluminate() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_get_iluminate(s)==FALSE);
  }

void test1_space_set_iluminate() {
  Space *s=NULL;
  s=space_create(1);
  space_set_iluminate(s, FALSE);
  PRINT_TEST_RESULT(space_get_iluminate(s)==FALSE);
  space_destroy(s);
  }

void test2_space_set_iluminate() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_set_iluminate(s, TRUE)==ERROR);
  }

void test1_space_set_up() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_set_up(s, 3)==ERROR);
  }

void test2_space_set_up() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_up(s, -1)==ERROR);
  space_destroy(s);
  }

void test3_space_set_up() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_up(s, 1)==OK);
  space_destroy(s);
  }

void test1_space_get_up() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_get_up(s)==NO_ID);
  }

void test2_space_get_up() {
  Space *s=NULL;
  s=space_create(2);
  space_set_up(s, 5);
  PRINT_TEST_RESULT(space_get_up(s)==5);
  space_destroy(s);
  }

void test1_space_set_down() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_set_down(s, 3)==ERROR);
  }

void test2_space_set_down() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_down(s, -1)==ERROR);
  space_destroy(s);
  }

void test3_space_set_down() {
  Space *s=NULL;
  s=space_create(3);
  PRINT_TEST_RESULT(space_set_down(s, 1)==OK);
  space_destroy(s);
  }

void test1_space_get_down() {
  Space *s=NULL;
  PRINT_TEST_RESULT(space_get_down(s)==NO_ID);
  }

void test2_space_get_down() {
  Space *s=NULL;
  s=space_create(2);
  space_set_down(s, 5);
  PRINT_TEST_RESULT(space_get_down(s)==5);
  space_destroy(s);
  }

/**
 * @brief It tests link module
 *
 * @file link_test.c
 * @author Andres Mena
 * @version 1.0
 * @date 29-03-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 28  /*!< Max amount of tests posible */

/**
 * @brief Main function for LINK unit tests.
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


  if (all || test == 1) test1_link_create();
  if (all || test == 2) test2_link_create();
  if (all || test == 3) test1_link_set_name();
  if (all || test == 4) test2_link_set_name();
  if (all || test == 5) test3_link_set_name();
  if (all || test == 6) test1_link_set_link1();
  if (all || test == 7) test2_link_set_link1();
  if (all || test == 8) test1_link_set_link2();
  if (all || test == 9) test2_link_set_link2();
  if (all || test == 10) test1_link_set_status();
  if (all || test == 11) test2_link_set_status();
  if (all || test == 12) test1_link_get_name();
  if (all || test == 13) test2_link_get_name();
  if (all || test == 14) test1_link_get_link1();
  if (all || test == 15) test2_link_get_link1();
  if (all || test == 16) test1_link_get_link2();
  if (all || test == 17) test2_link_get_link2();
  if (all || test == 18) test1_link_get_id();
  if (all || test == 19) test2_link_get_id();
  if (all || test == 20) test1_link_destroy();
  if (all || test == 21) test2_link_destroy();
  if (all || test == 22) test1_link_print();
  if (all || test == 23) test1_link_set_key();
  if (all || test == 24) test2_link_set_key();
  if (all || test == 25) test3_link_set_key();
  if (all || test == 26) test1_link_get_key();
  if (all || test == 27) test2_link_get_key();
  if (all || test == 28) test3_link_get_key();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_link_create() {
  Link *l=NULL;
  l=link_create(-1);
  PRINT_TEST_RESULT(l==NULL);
  }

void test2_link_create() {
  Link *l = NULL;
  l = link_create(4);
  PRINT_TEST_RESULT(link_get_id(l) == 4);
  link_destroy(l);
  }

void test1_link_set_name() {
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_name(l, "test") == OK);
  link_destroy(l);
}

void test2_link_set_name() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_name(l, "test") == ERROR);
  }

void test3_link_set_name() {
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_name(l, NULL) == ERROR);
  link_destroy(l);
  }

void test1_link_set_link1() {
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_link1(l, 4) == OK);
  link_destroy(l);
  }

void test2_link_set_link1() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_link1(l, 4) == ERROR);
  }

void test1_link_set_link2() {
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_link1(l, 4) == OK);
  link_destroy(l);
  }

void test2_link_set_link2() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_link1(l, 4) == ERROR);
  }

void test1_link_set_status() {
  Link *l = NULL;
  l = link_create(5);
  PRINT_TEST_RESULT(link_set_link1(l, CLOSE) == OK);
  link_destroy(l);
  }

void test2_link_set_status() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_status(l, OPEN) == ERROR);
  }

void test1_link_get_name() {
  Link *l = NULL;
  l = link_create(1);
  link_set_name(l, "adios");
  PRINT_TEST_RESULT(strcmp(link_get_name(l), "adios") == 0);
  link_destroy(l);
  }

void test2_link_get_name() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_name(l) == NULL);
  }


void test1_link_get_link1() {
  Link *l = NULL;
  l = link_create(5);
  link_set_link1(l, 4);
  PRINT_TEST_RESULT(link_get_link1(l) == 4);
  link_destroy(l);
  }

void test2_link_get_link1() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_link1(l) == NO_ID);
  }

void test1_link_get_link2() {
  Link *l = NULL;
  l = link_create(5);
  link_set_link2(l, 4);
  PRINT_TEST_RESULT(link_get_link2(l) == 4);
  link_destroy(l);
  }

void test2_link_get_link2() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_link2(l) == NO_ID);
  }

void test1_link_get_id() {
  Link *l = NULL;
  l = link_create(25);
  PRINT_TEST_RESULT(link_get_id(l) == 25);
  link_destroy(l);
  }

void test2_link_get_id() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_id(l) == NO_ID);
  }

void test1_link_destroy() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_destroy(l) == ERROR);
  }

void test2_link_destroy() {
  Link *l = NULL;
  l=link_create(1);
  PRINT_TEST_RESULT(link_destroy(l) == OK);
  }

void test1_link_print() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_print(l) == ERROR);
  }

void test1_link_set_key() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_key(l, 3) == ERROR);
  }

void test2_link_set_key() {
  Link *l = NULL;
  l=link_create(21);
  PRINT_TEST_RESULT(link_set_key(l, NO_ID) == ERROR);
  link_destroy(l);
  }

void test3_link_set_key() {
  Link *l = NULL;
  l=link_create(21);
  PRINT_TEST_RESULT(link_set_key(l, 3) == OK);
  link_destroy(l);
  }

void test1_link_get_key() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_key(l) == NO_ID);
  }

void test2_link_get_key() {
  Link *l = NULL;
  l=link_create(21);
  PRINT_TEST_RESULT(link_get_key(l) == 0);
  link_destroy(l);
  }

void test3_link_get_key() {
  Link *l = NULL;
  l=link_create(21);
  link_set_key(l, 3);
  PRINT_TEST_RESULT(link_get_key(l) == 3);
  link_destroy(l);
  }

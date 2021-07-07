/**
 * @brief It tests player module
 *
 * @file player_test.c
 * @author Andres Mena
 * @version 1.0
 * @date 31-03-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "player_test.h"
#include "test.h"
#include "inventory.h"
#include "player.h"


#define MAX_TESTS 16  /*!< Max amount of tests posible */

/**
 * @brief Main function for player unit tests.
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


  if (all || test == 1) test1_player_create();
  if (all || test == 2) test2_player_create();
  if (all || test == 3) test3_player_create();
  if (all || test == 4) test1_player_destroy();
  if (all || test == 5) test2_player_destroy();
  if (all || test == 6) test1_player_has_id();
  if (all || test == 7) test2_player_has_id();
  if (all || test == 8) test3_player_has_id();
  if (all || test == 9) test1_player_get_inventory();
  if (all || test == 10) test2_player_get_inventory();
  if (all || test == 11) test1_player_get_object();
  if (all || test == 12) test2_player_get_object();
  if (all || test == 13) test1_player_set_object();
  if (all || test == 14) test2_player_set_object();
  if (all || test == 15) test1_player_remove_object();
  if (all || test == 16) test2_player_remove_object();


  PRINT_PASSED_PERCENTAGE;

  return 1;
}


void test1_player_create() {
  Player *p=NULL;
  p=player_create(1);
  PRINT_TEST_RESULT(p!=NULL);
  player_destroy(p);
  }

void test2_player_create() {
  Player *p=NULL;
  p=player_create(4);
  PRINT_TEST_RESULT(player_get_id(p)==4);
  player_destroy(p);
  }

void test3_player_create() {
  Player *p=NULL;
  p=player_create(4);
  PRINT_TEST_RESULT(player_get_location(p)==0);
  player_destroy(p);
  }

void test1_player_destroy() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_destroy(p) == ERROR);
  }

void test2_player_destroy() {
  Player *p = NULL;
  p=player_create(2);
  PRINT_TEST_RESULT(player_destroy(p) == OK);
  }


void test1_player_get_object() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_object(p, 2) == NO_ID);
  }

void test2_player_get_object() {
  Player *p = NULL;
  p=player_create(2);
  player_set_object(p, 1);
  PRINT_TEST_RESULT(player_get_object(p, 0) == 1);
  player_destroy(p);
  }

void test1_player_set_object() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_object(p, 2) == ERROR);
  }


void test2_player_set_object() {
  Player *p = NULL;
  p=player_create(2);
  PRINT_TEST_RESULT(player_set_object(p, 5) == OK);
  player_destroy(p);
  }

void test1_player_remove_object() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_remove_object(p, 3) == ERROR);
  }

void test2_player_remove_object() {
  Player *p = NULL;
  p=player_create(2);
  player_set_object(p, 3);
  PRINT_TEST_RESULT(player_remove_object(p, 3) == OK);
  player_destroy(p);
  }

void test1_player_has_id() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_has_id(p, 1)==FALSE);
  }

void test2_player_has_id() {
  Player *p = NULL;
  p=player_create(4);
  PRINT_TEST_RESULT(player_has_id(p, 8)==FALSE);
  player_destroy(p);
  }

void test3_player_has_id() {
  Player *p = NULL;
  p=player_create(1);
  player_set_object(p, 1);
  PRINT_TEST_RESULT(player_has_id(p, 1)==TRUE);
  player_destroy(p);
  }

void test1_player_get_inventory() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_inventory(p)==NULL);
  }

void test2_player_get_inventory() {
  Player *p = NULL;
  Inventory *i=NULL;
  p=player_create(2);
  i=inventory_create();
  i=player_get_inventory(p);
  PRINT_TEST_RESULT(i!=NULL);
  inventory_destroy(i);
  }

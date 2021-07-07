/*
  Project: EDAT Lab 3 auxiliary material
  File: test.c
  Rev. 1.0
  Date: Nov. 9, 2018

  This is a simple program to test the table functions.
  It creates a table with four columns, of types

  [INT STR INT STR]

  creates a varaible number of tuples (the number is given in the
  command line) with random number and more or less random strings
  (they are generated as short strings of random length, and their
  content is taken as sub-string of a given string).  Then it reads
  back the strings twice: the first time it does so without closing
  the table. Then it closes the table, opens it again, and reads back
  all the tuples. It checks that the values read are the same as hose
  that were written in.

  The equality is checked using assert statements and, if the
  assertions are correct, they are printed on the screen for the
  satisfaction and amusement of the programmer.

  The test comes with a Makefile that compiles and executes it.
  Typing:

  make test

  with the source code in the same directory as the makefile should be
  enough to run the test.
*/

#include <stdio.h>
#include "type.h"
#include "table.h"
#include <time.h>
#include <string.h>
#include <limits.h>
#include <float.h>

/*
  Seed used to generate random strings and its length
*/

char seed[] = "let us go then you and i when the evening is spread out against the sky like a patient etherized upon a" \
  "table."								\
  " let us go through certain half-deserted streets, the muttering retreats of lonely night in one-night chaep" \
  "hotels, and restaurants with oyster shells";
int lmax;

char tablename[] = "testtable.dat";

/*
  Minimum and maximum of the length of a random string,
  and maximum integer and maximum double values defined
*/

#define MINLEN 5
#define MAXLEN 30

#define MAXINT 5000
#define MAXDBL 1000000.0

/*
  Frees the array of pointers created by _tuple. Receives the poiner
  to the array and the number of columns (viz., the number of elements
  in the array)
*/
void _tfree(void **values, int n) {
  for (int i=0; i<n; i++)
    free(values[i]);
  free(values);
  return;
}

/*
  Creates a random integer and returns it as a void-cast pointer to
  its value.
*/
void *_mk_int() {
  void *q = malloc(sizeof(int));
  *( (int *) q) = (int) rand() % MAXINT;
  return q;
}

/*
  Creates a random long long integer and returns it as a void-cast pointer to
  its value.
*/
void *_mk_llng() {
  void *q = malloc(sizeof(long long int));
  *( (long long int *) q) = (long long int) rand() % LLONG_MAX;
  return q;
}

/*
  Creates a random double precision number and returns it as a void-cast pointer to
  its value.
*/
void *_mk_dbl() {
  void *q = malloc(sizeof(double));
  *( (double *) q) = ((double)rand() / (double)RAND_MAX) * MAXDBL;
  return q;
}

/*
  Creates a random string, taking it as a random substring of the seed
*/
void *_mk_str() {
  int len = MINLEN + (rand() % (MAXLEN-MINLEN+1));
  int fst = rand() % (lmax-len);
  char *q = malloc(len+1);
  printf("%d %d\n", len, fst);
  memcpy(q, seed+fst, len);
  q[len] = 0;
  return (void *) q;
}

/*
  Generate random data for a tuple. The function receives the number of
  columns and an array with the types of the columns. Returns an array
  of void pointers to the values generated
*/
void **_tuple(int ncol, type_t *types) {
  void **q = (void **) malloc(ncol*sizeof(void *));
  for (int i=0; i<ncol; i++) {
    switch (types[i]) {
      case INT:
        q[i] = _mk_int();
        break;

      case DBL:
        q[i] = _mk_dbl();
        break;

      case LLNG:
        q[i] = _mk_llng();
        break;

      case STR:
        q[i] = _mk_str();
        break;

      default:
      fprintf(stderr, "Fatal error: unknown type %d on column %d\n", types[i], i);
      exit(1);
    }
  }
  return q;
}


int main(int argc, char **argv) {

  if (argc<2) {
    fprintf(stderr, "Usage: ./test <tuple_no>\n");
    exit(0);
  }
  int ntpl = atoi(argv[1]);
  if (ntpl<=0) {
    fprintf(stderr, "Number of tuples (%d) incorrect: must be positive.\n", ntpl);
    exit(0);
  }

  srand(time(NULL));
  lmax = strlen(seed);

  int ncols = 4;
  type_t types[] = {INT, LLNG, DBL, STR};

  void ***tuples = (void ***) malloc(ntpl*sizeof(void **));
  for (int i=0; i<ntpl; i++) {
    tuples[i] = _tuple(ncols, types);
  }
  /*
    Create a table, open it, and insert the tuples
  */
  table_create(tablename, ncols, types);

  table_t *tb = table_open(tablename);
  if (!tb) {
    fprintf(stderr, "Created table, but can't open it back (%s).\n", tablename);
    exit(0);
  }


  for (int i=0; i<ntpl; i++) {
    table_insert_record(tb, tuples[i]);
  }

  void **val = (void **) malloc(ncols*sizeof(void *));

  /*
    Now read them back from the table without closing it
  */
  printf("First test: reading back the values without closing the table\n");
  long pos = table_first_pos(tb);


  for (int i=0; i<ntpl; i++) {
    if ((pos=table_read_record(tb, pos)) < 0) {
      fprintf(stderr, "Fatal error in the first reading: only %d out of %d records read\n", i, ntpl);
      exit(0);
    }
    for (int col=0; col<ncols; col++) {
      val[col] = table_column_get(tb, col);
      print_value(stdout, types[col], val[col]);
      printf(", ");
    }
    printf("\n");
    for (int col=0; col<ncols; col++) {
      print_value(stdout, types[col], tuples[i][col]);
      printf(", ");
    }
    printf("\n\n\n");

    for (int col=0; col<ncols; col++) {
      if (value_cmp(types[col], val[col], tuples[i][col])) {
	fprintf(stdout, "Error: tuples discrepancy!\n");
	exit(1);
      }
    }

  }

  /*
    Now read them back from the table without closing it
  */
  printf("\n\nSecond test: reading back the valuesafter closing the table and opening it again\n");
  table_close(tb);

  tb = table_open(tablename);
  pos = table_first_pos(tb);


  for (int i=0; i<ntpl; i++) {
    if ((pos=table_read_record(tb, pos)) < 0) {
      fprintf(stderr, "Fatal error in the first reading: only %d out of %d records read\n", i, ntpl);
      exit(0);
    }
    for (int col=0; col<ncols; col++) {
      val[col] = table_column_get(tb, col);
      print_value(stdout, types[col], val[col]);
      printf(", ");
    }
    printf("\n");
    for (int col=0; col<ncols; col++) {
      print_value(stdout, types[col], tuples[i][col]);
      printf(", ");
    }
    printf("\n\n\n");

    for (int col=0; col<ncols; col++) {
      if (value_cmp(types[col], val[col], tuples[i][col])) {
	fprintf(stdout, "Error: tuples discrepancy!\n");
	exit(1);
      }
    }

  }

  fprintf(stdout, "Everything working just as expected, test passed successfully!\n");

}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "table.h"
#include "type.h"

struct table_ {
  FILE *fp;
  int ncols;
  type_t *types;
  void **values;
};

/*
   Creates a file that stores an empty table. This function doesn't
   keep any information in memory: it simply creates the file, stores
   the header information, and closes it.
*/
void table_create(char* path, int ncols, type_t* types) {
  if(path == NULL || types == NULL)
    return;

  FILE *f = fopen(path, "w+");
    if(f == NULL)
      return;

  fwrite(&ncols, sizeof(int), 1, f);
  fwrite(types, sizeof(type_t), ncols, f);

  fclose(f);
  return;
}


/*
   Opens a table given its file name. Returns a pointer to a structure
   with all the information necessary to manage the table. Returns
   NULL if the file doesn't exist or if there is any error.
*/


table_t* table_open(char* path) {
  int ncols;

  table_t *table = (table_t *)malloc(sizeof(table[0]));
  if (table==NULL)
    return NULL;

  table->fp = fopen (path, "r+");
  if (table->fp==NULL){
    free (table);
    return NULL;
  }

  fseek(table->fp, 0, SEEK_SET);
  fread (&ncols, 1, sizeof(ncols), table->fp);
  table->ncols = ncols;

  table->types = (type_t *) malloc(ncols*sizeof(type_t));
  if(table->types == NULL){
    fclose (table->fp);
    free (table);
    return NULL;
  }

  table->values = (void **) malloc(ncols*sizeof(void *));
  if(table->values == NULL){
    fclose (table->fp);
    free (table->types);
    free (table);
    return NULL;
  }

  fread (table->types, table->ncols, sizeof(type_t), table->fp);

  return table;
}

/*
   Closes a table freeing the alloc'ed resources and closing the file
   in which the table is stored.
*/

void table_close(table_t* table) {
  free (table->values);
  free(table->types);
  fclose(table->fp);
  free (table);
}

/*
   Returns the number of columns of the table
*/
int table_ncols(table_t* table) {
  return table->ncols;
}

/*
   Returns the array with the data types of the columns of the
   table. Note that typically this kind of function doesn't make a
   copy of the array, rather, it returns a pointer to the actual array
   contained in the table structure. This means that the calling
   program should not, under any circumstance, modify the array that
   this function returns.
 */
type_t* table_types(table_t* table) {
  return table->types;
}

/*
   Returns the position in the file of the first record of the table
*/
long table_first_pos(table_t* table) {
  return sizeof(int)+sizeof(type_t)*table->ncols;
}

/*
   Returns the position in the file in which the table is currently
   positioned.
*/
long table_cur_pos(table_t* table) {
  return ftell (table->fp);
}

/*
   Returns the position just past the last byte in the file, where a
   new record should be inserted.
*/
long table_last_pos(table_t* table) {
  long aux = ftell(table->fp);
  fseek (table->fp, 0, SEEK_END);
  long new = ftell (table->fp);
  fseek (table->fp, aux, SEEK_SET);
  return new;
}

/*
   Reads the record starting in the specified position. The record is
   read and stored in memory, but no value is returned. The value
   returned is the position of the following record in the file or -1
   if the position requested is past the end of the file.
*/
long table_read_record(table_t* table, long pos) {
  int rlen, i;

  if (pos>table_last_pos(table)){
    printf ("Error in table_read_record\n");
    return -1L;
  }

  fseek (table->fp, pos, SEEK_SET);
  fread (&rlen, 1, sizeof(int), table->fp);

  char *buff = (char *) malloc (rlen*sizeof(char));
  fread (buff, sizeof(char), rlen, table->fp);

  for(i=0; i < table->ncols; i++){
    table->values[i] = buff;
    buff += value_length(table->types[i], buff);
  }
  return table_cur_pos(table);
}



/*
  Returns a pointer to the value of the given column of the record
  currently in memory. The value is cast to a void * (it is always a
  pointer: if the column is an INT, the function will return a pointer
  to it).. Returns NULL if there is no record in memory or if the
  column doesn't exist.
*/
void *table_column_get(table_t* table, int col) {
  return table->values[col];
}


/*
   Inserts a record in the last available position of the table. Note
   that all the values are cast to void *, and that there is no
   indication of their actual type or even of how many values we ask
   to store... why?
  */

void table_insert_record(table_t* table, void** values) {
  int len = 0;

  fseek(table->fp, 0, SEEK_END);
  for (int i=0; i<table->ncols; i++)
      len += value_length(table->types[i], values[i]);

  fwrite(&len, 1, sizeof(int), table->fp);

  for (int i=0; i<table->ncols; i++)
      fwrite(values[i], 1, value_length(table->types[i], values[i]), table->fp);
}

#include <stdio.h>
#include "type.h"
#include "table.h"
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "index.h"

int main(int argc, char **argv) {
  /*Error management*/
  if (argc<2) {
    fprintf(stderr, "Not enough params.\nFormat must be: ./test2 filename\n");
    exit(0);
  }

  if (argc>2) {
    fprintf(stderr, "Too many params.\nFormat must be: ./test2 filename\n");
    exit(0);
  }

  char *indexname=(char *)malloc((strlen(argv[1])+1)*sizeof(char));
  if (indexname == NULL)
    return -1;

  strcpy (indexname, argv[1]);

  /*First, we create an index*/
  if ((index_create(INT, indexname) == -1)){
    printf("Unable to create index.\n");
    return -1;
  }

  /*Now, we open the index*/
  index_t *index = index_open(indexname);
  if(index == NULL){
    printf("Unable to open index\n");
    return -1;
  }

  /* Now we insert some hypothetical scores in our index (in position 1)*/
  if(index_put(index, 25, 1) == -1){
    printf( "Error in index_put\n");
    index_close(index);
    return -1;
  }


  /* Now we insert some hypothetical scores in our index (in position 2) */
  if(index_put(index, 50, 2) == -1){
    printf( "Error in index_put\n");
    index_close(index);
    return -1;
  }

  /*we try to find a key that doesn't exist*/
  int pos=0;
  long *aux = index_get(index, 1, &pos);
  if(aux != NULL){
    printf( "Error in index_get\n");
    index_close(index);
    return -1;
  }

  /*find a key that exist*/
  aux = index_get(index, 50, &pos);
  if(aux == NULL){
    printf( "Error in index_get\n");
    index_close(index);
    return -1;
  }

  /*we save our index, save it, and free resources*/
  free (indexname);
  index_save(index);
  index_close(index);
  fprintf(stdout, "Everything working just as expected, test passed successfully!\n");
  return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "index.h"
#include "type.h"

/*Neccesary structures to manage the index*/
struct irecord_{
  int key;
  int npt;
  long *pt;
};


struct index_ {
    int nkeys;
    char *path;
    irecord **keys;
    type_t *key_type;
};

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(irecord **arr, int n){
   for (int i = 0; i < n-1; i++)
       for (int j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap((int *)arr[j], (int *)arr[j+1]);
}

/*int mycmp(const void *kptr, const void *e) {
  irecord *rec = *((irecord **) e);
  if (key < rec->key)
    return -1;
  else if (key > rec->key)
    return 1;
  else
    return 0;
}*/


/*
   Creates a file for saving an empty index. The index is initialized
   to be of the specific tpe (in the basic version this is always INT)
   and to contain 0 entries.
 */
 int index_create(int type, char *path) {
   int tam = 0;
   if (path==NULL)
     return -1;

   FILE *f = fopen(path,"w+");
   if (f == NULL)
    return -1;

   fwrite(&type,sizeof(type), 1, f);
   fwrite(&tam, sizeof(tam), 1, f);

   fclose(f);

   return 0;
 }

/*
   Opens a previously created index: reads the contents of the index
   in an index_t structure that it allocates, and returns a pointer to
   it (or NULL if the files doesn't exist or there is an error).

   NOTE: the index is stored in memory, so you can open and close the
   file in this function. However, when you are asked to save the
   index, you will not be given the path name again, so you must store
   in the structure either the FILE * (and in this case you must keep
   the file open) or the path (and in this case you will open the file
   again).
 */
index_t* index_open(char* path) {
  if (path == NULL)
    return NULL;

  index_t *index = (index_t *)malloc(sizeof(index_t));
  if (index == NULL)
    return NULL;

  index->path = (char *)malloc((strlen(path)+1)*sizeof(char));
  if (index->path == NULL){
    free (index);
    return NULL;
  }

  index->key_type=(type_t*) malloc(sizeof(type_t));
  if(index->key_type==NULL) {
      free(index->path);
      free(index);
      return NULL;
  }

  strcpy (index->path, path);
  FILE *fp=fopen(path, "ab+");
  if (fp == NULL){
    free (index->path);
    free (index->key_type);
    free (index);
    return NULL;
  }

  fseek(fp, 0, SEEK_SET);
  /*read the information of the file into the structure*/
  fread(index->key_type, sizeof(type_t), 1, fp);
  fread(&(index->nkeys), sizeof(int),1, fp);

  if(index->nkeys<0){
    free(index->key_type);
    free(index->path);
    free(index);
    fclose(fp);
    return NULL;
  }

  else if (index->nkeys == 0){
    index->keys = NULL;
    return index;
  }


  index->keys = (irecord**) malloc(index->nkeys*sizeof(irecord*));
  for (int i = 0; i < index->nkeys ; i++) {
    index->keys[i] = (irecord*) malloc(sizeof(irecord));
    fread(&(index->keys[i]->key), sizeof(int), 1, fp);
    fread(&(index->keys[i]->npt), sizeof(int), 1, fp);
    index->keys[i]->pt = (long*) malloc(index->keys[i]->npt*sizeof(long));
    fread(index->keys[i]->pt, sizeof(long), index->keys[i]->npt, fp);

  }
  fclose(fp);
  return index;
}

/*
   Saves the current state of index in the file it came from. See the
   NOTE to index_open.
*/
int index_save(index_t* index) {
  if (index == NULL)
    return -1;

  FILE *fp= fopen (index->path,"w+");
  fwrite(index->key_type, sizeof(int), 1, fp);
  fwrite(&index->nkeys, sizeof(int), 1, fp);

  /*print in the file the keys and the number of records*/
  for (int i = 0; i < index->nkeys; i++) {
    fwrite(&(index->keys[i]->key), sizeof(int), 1, fp);
    fwrite(&(index->keys[i]->npt), sizeof(int), 1, fp);

    for (int j = 0; j < index->keys[i]->npt; j++) {
      fwrite(&(index->keys[i]->pt[j]), sizeof(long),1, fp);
    }
  }
  fclose (fp);
  return 0;
}



/*
   Puts a pair key-position in the index. Note that the key may be
   present in the index or not... you must manage both situation. Also
   remember that the index must be kept ordered at all times.
*/
int index_put(index_t *index, int key, long pos) {
  if (index==NULL)
    return -1;

  int p = 0, u=index->nkeys -1, m;

  /*We check if we already have the key*/
  while (p <= u) {
    m = (p + u) / 2;
    if (index->keys[m]->key == key) {

      if(index->keys[m]->npt == 0){
        index->keys[m]->pt = (long *)malloc(sizeof(long));
        if(index->keys[m]->pt == NULL)
          return -1;
      }

      else{
        index->keys[m]->pt = (long *)realloc(index->keys[m]->pt, (index->keys[m]->npt + 1)* sizeof(long));
        if(index->keys[m]->pt == NULL)
          return -1;
      }

      index->keys[m]->pt[index->keys[m]->npt] = pos;
      index->keys[m]->npt++;

      return 0;
    }

    else if (index->keys[m]->key > key) {
      u = m-1;
    }

    else {
      p = m+1;
    }
  }

  /*If we cannot find the key, we create it*/
  irecord *aux = (irecord *)malloc(sizeof(irecord));
  if (aux == NULL)
    return -1;

  aux->npt = 0;
  aux->pt = NULL;
  aux->key = key;

  if(index->nkeys == 0){
    index->keys = (irecord **) malloc(sizeof(irecord *));

    if (index->keys == NULL){
      free (aux);
      return -1;
    }
  }

  else
    index->keys = (irecord **) realloc(index->keys, (index->nkeys + 1) * sizeof(irecord *));

  index->keys[index->nkeys] = aux;
  index->nkeys++;

  if(index->keys[index->nkeys-1]->npt == 0){
    index->keys[index->nkeys-1]->pt = (long *)malloc(sizeof(long));
    if(index->keys[index->nkeys-1]->pt == NULL)
      return -1;
  }

  else{
    index->keys[index->nkeys-1]->pt = (long *)realloc(index->keys[index->nkeys-1]->pt, (index->keys[index->nkeys-1]->npt + 1) * sizeof(long));
    if(index->keys[index->nkeys-1]->pt == NULL)
      return -1;
  }

  index->keys[index->nkeys-1]->pt[index->keys[index->nkeys-1]->npt]=pos;
  index->keys[index->nkeys-1]->npt++;
  bubbleSort(index->keys,index->nkeys);
  return 0;
}

/*
   Retrieves all the positions associated with the key in the index.

   NOTE: the parameter nposs is not an array of integers: it is
   actually an integer variable that is passed by reference. In it you
   must store the number of elements in the array that you return,
   that is, the number of positions associated to the key. The call
   will be something like this:

   int n
   long **poss = index_get(index, key, &n);

   for (int i=0; i<n; i++) {
       Do something with poss[i]
   }

   ANOTHER NOTE: remember that the search for the key MUST BE DONE
   using binary search.

*/
long *index_get(index_t *index, int key, int* nposs) {
  if (index == NULL || nposs == NULL)
    return NULL;

  int p = 0;
  int u = index->nkeys - 1;
  int m;

  if (p > u)
    return NULL;

  while (p <= u) {
    m = (p+u)/2;
    if (index->keys[m]->key == key) {
      *nposs = index->keys[m]->npt;
      return index->keys[m]->pt;
    }

    else{
      if (index->keys[m]->key > key)
        u = m-1;

      else
        p = m+1;
      }
    }
    return NULL;
  }

/*
   Closes the index by freeing the allocated resources
*/
void index_close(index_t *index) {
  if (index == NULL)
    return;

  if (index->keys != NULL) {
    for (int i = 0; i < index->nkeys; i++) {
      if (index->keys[i] != NULL) {
        free(index->keys[i]->pt);
      }
      free(index->keys[i]);
    }
    free(index->keys);
  }
  free (index->key_type);
  free (index->path);
  free(index);
}

/**
 * @brief Define el TAD CAD(trabaja con cadenas de caracteres)
 *
 * @file cad.c
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0
 * @date 30-04-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cad.h"
#define MAX_WORD 1024

/**
* @brief Crea e inicializa una cadena de caracteres.
* @date 30/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param
* @return char* cad
*/

char* cadena_ini() {
  char *cad = NULL;

  cad = (char*)malloc(MAX_WORD*sizeof(char));

  if (cad == NULL) {
    return NULL;
  }

  return cad;
}

/**
* @brief Destruye la cadena de caractwres
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param char* cadena
* @return
*/

void cadena_free(char *cadena) {
  if (cadena == NULL) {
    return;
  }

  free(cadena);
}

/**
* @brief hace una copia de una cadena
* reservando memoria para ella
* @date 30/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param char*cadena
* @return char* copia
*/

char* cadena_copy(char *cadena) {
   char *copia = NULL;

  if (cadena == NULL) {
    return NULL;
  }

  copia = cadena_ini();

  if (copia == NULL) {
    return NULL;
  }

  strcpy(copia, cadena);

  return copia;
}

/**
* @brief realiza una comparacion entre
* dos cadenas dadas
* @date 30/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param char* cad1
* @param char* cad2
* @return int
*/

int cadena_cmp(char *cad1, char *cad2) {
  if (cad1 == NULL || cad2 == NULL) {
    return -1;
  }

  if (strcmp(cad1, cad2) == 0) {
    return 0;
  }else if (strcmp(cad1, cad2) > 0) {
    return 1;
  }else {
    return -1;
  }
}

/**
* @brief imprime el valor de una cadena
* @date 30/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param FILE* pf
* @param char* cadena
* @return bytes, numero de caracteres
*/

int cadena_print(FILE *f, char *cadena) {
  int bytes = 0;

  if (f == NULL || cadena  == NULL) {
    return -1;
  }

  bytes += fprintf(f, "%s ", cadena);

  return bytes;
}

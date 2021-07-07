/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "permutaciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/***************************************************/
/* Funcion: aleat_num Fecha: 28/09/2018            */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/

int aleat_num(int inf, int sup)
{
  assert(inf >= 0);
  assert(sup >= inf);

  return inf + rand() % (sup-inf+1);
}

/***************************************************/
/* Funcion: genera_perm Fecha: 28/09/2018          */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Rutina que genera una permutación               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int N: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/

int* genera_perm(int N)
{
  int i;
  int* perm;

  perm = (int*)malloc(N*sizeof(int));

  if(!perm)
    return NULL;

  for(i=0; i < N; i++)
    perm[i] = i+1;

  for(i=0; i < N; i++) {
    swap(&perm[i], &perm[aleat_num(i, N-1)]);
  }
  return perm;
}

/***************************************************/
/* Funcion: swap Fecha: 28/09/2018                 */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Función que intercambia dos elementos           */
/*                                                 */
/* Entrada:                                        */
/* int *p: Primer numero a intercambiar            */
/* int *p: Segundo numero a intercambiar           */
/*                                                 */
/* Salida:                                         */
/* void                                            */
/***************************************************/

void swap(int *p, int *q){
  int d;

  d = *p;
  *p = *q;
  *q = d;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 28/09/18   */
/* Autores: Andrés Mena y Juan Moreno              */
/*                                                 */
/* Rutina que realiza un intercambio               */
/* de dos números enteros                          */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/

int** genera_permutaciones(int n_perms, int N)
{
  int **perm;
  int i, j;

  perm = (int**)malloc(n_perms*sizeof(perm[0]));

  if(perm == NULL)
    return NULL;

  for(i=0; i < n_perms; i++){
    perm[i] = genera_perm(N);
      if(perm[i] == NULL){
        for(j=0; j < i; j++)
        free(perm[j]);

        free(perm);
        return NULL;
      }
  }
  return perm;
}

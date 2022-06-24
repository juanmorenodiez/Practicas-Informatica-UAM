/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "ordenacion.h"
#include "permutaciones.h"

/***************************************************/
/* Funcion: SelectSort Fecha: 05/10/2018            */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Función que busca el mínimo elemento            */
/* de una tabla y lo compara con los elementos     */
/* anteriores para intercambiarlos y ordenarlos    */
/* de forma ascendente.                            */
/*                                                 */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla a ordenar                     */
/* int ip: primer elemento de la tabla             */
/* int iu: último elemento de la tabla             */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o            */
/* el número de veces que se ha ejecutado la OB    */
/* en el caso de que la tabla se ordene            */
/* correctamente.                                  */
/***************************************************/

int SelectSort(int* tabla, int ip, int iu)
{
  int i, cont_obs=0;

  for(i=ip; i<iu; i++){
    int min = minimo(tabla, i, iu);
    swap(&tabla[i], &tabla[min]);
    cont_obs+=(iu-i);
  }
  return cont_obs;
}

/***************************************************/
/* Funcion: minimo Fecha: 5/10/2018                */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Rutina que busca el elemento                    */
/* mínimo de la tabla                              */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de elementos                  */
/* int ip: primer elemento de la tabla             */
/* int iu: último elemento de la tabla             */
/* Salida:                                         */
/* int: numero mínimo de la tabla                  */
/***************************************************/

int minimo(int *tabla, int ip, int iu){
  int min;
  int i;

  min = ip;

  for(i=ip+1; i <= iu; i++){
    if(tabla[i] < tabla[min])
    min = i;
  }

  return min;
}

/***************************************************/
/* Funcion: maximo Fecha: 05/10/2018            */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Rutina que busca el elemento máximo             */
/* de la tabla                                     */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla de elementos                  */
/* int ip: primer elemento de la tabla             */
/* int iu: último elemento de la tabla             */
/* Salida:                                         */
/* int: numero máximo de la tabla                  */
/***************************************************/

int maximo(int *tabla, int ip, int iu){
  int max;
  int i;

  max = ip;

  for(i=ip+1; i <= iu; i++){
    if(tabla[i] > tabla[max])
    max = i;
  }

  return max;
}

/***************************************************/
/* Funcion: SelectSortInv Fecha: 05/10/2018        */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Función que busca el mínimo elemento            */
/* de una tabla y lo compara con los elementos     */
/* anteriores para intercambiarlos y ordenarlos    */
/* de forma descendente.                           */
/*                                                 */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla a ordenar                     */
/* int ip: primer elemento de la tabla             */
/* int iu: último elemento de la tabla             */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o            */
/* el número de veces que se ha ejecutado la OB    */
/* en el caso de que la tabla se ordene            */
/* correctamente.                                  */
/***************************************************/

int SelectSortInv(int* tabla, int ip, int iu)
{
  int i, cont_obs=0;

  for(i=ip; i<iu; i++){
    int max = maximo(tabla, i, iu);
    swap(&tabla[i], &tabla[max]);
    cont_obs+=(iu-i);
  }

  return cont_obs;

}

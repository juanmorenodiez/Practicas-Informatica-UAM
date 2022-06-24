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
#include <stdlib.h>

/***************************************************/
/* Funcion: SelectSort Fecha: 05/10/2018           */
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
  int i, obs=0;

  for(i=ip; i<iu; i++){
    int min = minimo(tabla, i, iu);
    swap(&tabla[i], &tabla[min]);
    obs+=(iu-i);
  }
  return obs;
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
/* Funcion: maximo Fecha: 05/10/2018               */
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
  int i, obs=0;

  for(i=ip; i<iu; i++){
    int max = maximo(tabla, i, iu);
    swap(&tabla[i], &tabla[max]);
    obs+=(iu-i);
  }

  return obs;

}

/***************************************************/
/* Funcion: merge Fecha: 18/11/2018                */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Función de combinación que utilizaremos         */
/* en el algoritmo MergeSort para ordenar          */
/* la tabla de forma correcta.                     */
/*                                                 */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla a ordenar                     */
/* int ip: primer elemento de la tabla             */
/* int iu: último elemento de la tabla             */
/* int imedio: elemento medio de la tabla          */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o            */
/* el número de veces que se ha ejecutado la OB    */
/***************************************************/

int merge(int* tabla, int ip, int iu, int imedio){
  int i = 0, k = 0 , j = 0, obs = 0;
  int *aux;

  if(tabla == NULL || iu < ip || imedio < ip || iu < imedio){
    return ERR;
  }

  aux = (int*)malloc((iu-ip+1)*sizeof(int));
  if(aux == NULL)
    return ERR;

  i = ip;
  j = imedio + 1;

  while(i <= imedio && j <= iu){
    if(tabla[i] < tabla[j]){
      aux[k] = tabla[i];
      i++;
      obs++;
    }
    else  {
      aux[k] = tabla[j];
      j++;
      obs++;

    }

      k++;

    }

  if(i > imedio)
      while(j <= iu){
        aux[k] = tabla[j];
        j++;
        k++;
      }
  else if(j > iu)
    while(i <= imedio){
      aux[k] = tabla[i];
      i++;
      k++;
    }

  for(i=0 ; i <= iu-ip; i++)
    tabla[ip+i] = aux[i];

  free(aux);

  return obs;
}

/***************************************************/
/* Funcion: mergesort Fecha: 18/11/2018            */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Función que mediante la rutina                  */
/* merge, ordena una tabla de menor a              */
/* mayor para un tamaño que nosotros               */
/* introduzcamos  por pantalla.                    */
/*                                                 */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla a ordenar                     */
/* int ip: primer elemento de la tabla             */
/* int iu: último elemento de la tabla             */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o            */
/* el número de veces que se ha ejecutado la OB    */
/***************************************************/

int mergesort(int* tabla, int ip, int iu){
  int m, obs=0, ret;

  if (ip>iu || tabla == NULL)
    return ERR;

  else if (ip==iu)
    return 0;

  else{
    m=(ip+iu)/2;
    ret = mergesort(tabla, ip, m);
    if(ret == ERR)
      return ERR;

    obs+=ret;

    ret = mergesort(tabla, m+1, iu);
    if(ret == ERR)
      return ERR;

    obs+=ret;

    ret = merge(tabla, ip, iu, m);
    if(ret == ERR)
      return ERR;

    obs+=ret;
  }

  return obs;
}

/***************************************************/
/* Funcion: quicksort Fecha: 18/11/2018            */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Función que mediante la rutina                  */
/* partir, ordena una tabla de menor a             */
/* mayor para un tamaño que nosotros               */
/* introduzcamos por pantalla.                     */
/*                                                 */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla a ordenar                     */
/* int ip: primer elemento de la tabla             */
/* int iu: último elemento de la tabla             */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o            */
/* el número de veces que se ha ejecutado la OB    */
/***************************************************/

int quicksort(int* tabla, int ip, int iu){
  int pivote=0, obs_aux1=0, obs_aux2=0, obs_aux3=0;

  if (ip>iu)
    return ERR;

  else if (ip==iu)
    return 0;

  else{
    if ((obs_aux1=partir(tabla, ip, iu, &pivote))==ERR)
      return ERR;

    if (ip < pivote-1)
      if ((obs_aux2=quicksort(tabla, ip, pivote-1))==ERR)
        return ERR;


    if (pivote+1 < iu)
      if ((obs_aux3=quicksort(tabla, pivote+1, iu))==ERR)
        return ERR;
  }

  return obs_aux1+obs_aux2+obs_aux3;
}

/***************************************************/
/* Funcion: partir    Fecha: 18/11/2018            */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Función que va partiendo la tabla               */
/* de elementos según la posición de               */
/* un determinado elemento y la ordena.            */
/*                                                 */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla a ordenar                     */
/* int ip: primer elemento de la tabla             */
/* int iu: último elemento de la tabla             */
/* int *pos: argumento que se utiliza              */
/* para devolver la posición del pivote            */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o            */
/* el número de veces que se ha ejecutado la OB    */
/***************************************************/

int partir(int* tabla, int ip, int iu, int *pos){
  int i, k, obs=0;

  if(ip > iu){
    return ERR;
  }

  medio(tabla, ip, iu, pos);

  k = tabla[*pos];
  swap(&tabla[ip], &tabla[*pos]);

  *pos = ip;

  for(i=ip+1; i <= iu; i++){
    if(tabla[i] < k){
      (*pos)++;
      swap(&tabla[i], &tabla[*pos]);
    }
    obs++;
  }

  swap(&tabla[ip], &tabla[*pos]);

  return obs;
}

/***************************************************/
/* Funcion: medio   Fecha: 18/11/2018              */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Función que le asigna a *pos                    */
/* el primer elemento de la tabla                  */
/* para luego utilizarlo(*pos) como                */
/* pivote.                                         */
/*                                                 */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla a ordenar                     */
/* int ip: primer elemento de la tabla             */
/* int iu: último elemento de la tabla             */
/* int *pos: argumento que se utiliza              */
/* para devolver la posición del pivote            */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o            */
/* 0 en caso de que la asignación se haya          */
/* realizado correctamente                         */
/***************************************************/

int medio(int *tabla, int ip, int iu, int *pos){
  if (ip > iu)
    return ERR;

  *pos=ip;

  return 0;
}

/***************************************************/
/* Funcion: quicksort_src Fecha: 18/11/2018        */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Función que hemos implementado                  */
/* de forma muy parecida al quicksort              */
/* pero eliminando la recursión de cola           */
/* para comparar los resultados entre los dos      */
/* algoritmos.                                     */
/*                                                 */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla a ordenar                     */
/* int ip: primer elemento de la tabla             */
/* int iu: último elemento de la tabla             */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o            */
/* el número de veces que se ha ejecutado la OB    */
/***************************************************/

int quicksort_src(int* tabla, int ip, int iu){
  int pivote=0, obs_aux1=0, obs=0;

  if (ip==iu)
    return 0;

  while (ip<iu){
    if ((obs_aux1=partir(tabla, ip, iu, &pivote))==ERR)
      return ERR;

    obs+=obs_aux1;

    if ((obs_aux1=quicksort_src(tabla, ip, pivote-1))==ERR)
        return ERR;

    obs+=obs_aux1;

    ip=pivote+1;
  }

  return obs;
}

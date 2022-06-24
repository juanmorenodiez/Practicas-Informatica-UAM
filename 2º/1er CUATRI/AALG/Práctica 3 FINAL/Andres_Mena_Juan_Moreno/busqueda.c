/**
 *
 * Descripcion: Implementacion funciones para busqueda
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"

#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/***************************************************/
/* Funcion: ini_diccionario Fecha: 14/12/2018      */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Rutina que crea un diccionario del              */
/* tipo indicado por sus argumentos                */
/*                                                 */
/* Entrada:                                        */
/* int tamanio: tamaño del diccionario             */
/* char orden: indica si el diccionario            */
/* está ordenado o no                              */
/* Salida:                                         */
/* PDICC: puntero a la estructura del              */
/* diccionario                                     */
/***************************************************/

PDICC ini_diccionario (int tamanio, char orden){

  PDICC diccionario = (PDICC) malloc (sizeof(DICC));
  if (diccionario == NULL)
    return NULL;

  diccionario->tamanio = tamanio;
  diccionario->orden = orden;
  diccionario->n_datos = 0;
  diccionario->tabla = (int *)malloc(tamanio*sizeof(diccionario->tabla[0]));
  if (diccionario->tabla == NULL){
    free (diccionario);
    return NULL;
  }

  return diccionario;
}

/***************************************************/
/* Funcion: libera_diccionario Fecha: 14/12/2018   */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Rutina que libera toda la memoria               */
/* reservada por las funciones del TAD             */
/*                                                 */
/* Entrada:                                        */
/* PDICC pdicc: puntero a la estructura            */
/* del diccionario                                 */
/* Salida:                                         */
/* void:                                           */
/***************************************************/

void libera_diccionario(PDICC pdicc)
{
  free(pdicc->tabla);
  free(pdicc);
}

/***************************************************/
/* Funcion: inserta_diccionario Fecha: 14/12/2018  */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Rutina que introduce el elemento clave          */
/* en la posición correcta del diccionario         */
/* definido por pdicc                              */
/*                                                 */
/* Entrada:                                        */
/* PDICC pdicc: puntero a la estructura            */
/* diccionario                                     */
/* int clave: clave a insertar                     */
/* Salida:                                         */
/* int: numero de obs                              */
/***************************************************/

/*DECIDIMOS QUE INSERTAR UN ELEMENTO ES UNA SOLA OB*/
/*CADA COMPARACION DE CLAVE ES UNA OB*/
int inserta_diccionario(PDICC pdicc, int clave)
{
  int obs=1;
  if (pdicc->tamanio <= pdicc->n_datos)
    return ERR;

  pdicc->tabla[pdicc->n_datos] = clave;
  pdicc->n_datos += 1;


  if (pdicc -> orden == ORDENADO){
    int j = pdicc->n_datos - 2;

    while (j >= 0 && pdicc->tabla[j]>clave){
      obs+=1;
      pdicc->tabla[j+1]=pdicc->tabla[j];
      j--;
    }
    obs+=1;
    pdicc->tabla[j+1]=clave;
  }

	return obs;
}

/****************************************************************/
/* Funcion: insercion_masiva_diccionario Fecha: 14/12/2018      */
/* Autores: Juan Moreno y Andrés Mena                           */
/*                                                              */
/* Rutina que las n_claves claves en el diccionario             */
/* mediante la realización de n_claves sucesivas                */
/* a la función inserta_diccionario                             */
/*                                                              */
/* Entrada:                                                     */
/* PDICC pdicc: puntero a la estructura diccionario             */
/* int *claves: tabla claves                                    */
/* int n_claves: número de claves                               */
/* Salida:                                                      */
/* int: número de obs                                           */
/****************************************************************/

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves){
  int i, obs_aux, obs=0;

  for (i=0; i < n_claves; i++){
    if ((obs_aux=inserta_diccionario(pdicc, claves[i]))==ERR)
      return ERR;
    obs+=obs_aux;
  }

  return obs;
}

/***************************************************/
/* Funcion: busca_diccionario Fecha: 14/12/2018    */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Rutina que crea un diccionario del              */
/* tipo indicado por sus argumentos                */
/*                                                 */
/* Entrada:                                        */
/* PDICC pdicc: puntero a la estructura            */
/* diccionario                                     */
/* int clave: clave a buscar                       */
/* int *ppos: índice donde se encontará la clave   */
/* pfunc_busqueda metodo: método de búsqueda       */
/* a utilizar                                      */
/* Salida:                                         */
/* int: número de obs                              */
/***************************************************/

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
	return metodo (pdicc->tabla, 0, pdicc->n_datos, clave, ppos);
}

/* Funciones de busqueda del TAD Diccionario */

/***************************************************/
/* Funcion: bbin Fecha: 14/12/2018                 */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Rutina que busca un elemento en una tabla       */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla en la que buscan un elemento  */
/* int p: primer elemento de la tabla              */
/* int u: ultimo elemento de la tabla              */
/* int clave: clave a buscar                       */
/* int *ppos: índice donde se encontará la clave   */
/* Salida:                                         */
/* int: número de obs                              */
/***************************************************/

int bbin(int *tabla,int p,int u,int clave,int *ppos){
  int m, obs=0;

  if (p>u)
    return ERR;

	while (p <= u){
      m = (p+u)/2;
      obs+=1;
      if (tabla[m] == clave){
        *ppos = m;
        return obs;
      }

      else{
        if (tabla[m] > clave)
          u = m - 1;

        else
          p = m + 1;
      }
  }
  *ppos=NO_ENCONTRADO;
  return obs;
}

/***************************************************/
/* Funcion: blin Fecha: 14/12/2018                 */
/* Autores: Juan Moreno y Andrés Mena              */
/*                                                 */
/* Rutina que busca un elemento en una tabla       */
/*                                                 */
/* Entrada:                                        */
/* int *tabla: tabla en la que buscan un elemento  */
/* int p: primer elemento de la tabla              */
/* int u: ultimo elemento de la tabla              */
/* int clave: clave a buscar                       */
/* int *ppos: índice donde se encontará la clave   */
/* Salida:                                         */
/* int: número de obs                              */
/***************************************************/

int blin(int *tabla, int p, int u, int clave, int *ppos){
  int i, obs=0;

  for(i=p; i < u; i++){
    obs+=1;
    if(clave == tabla[i]){
      *ppos = i;
      return obs;
    }
  }
  *ppos=NO_ENCONTRADO;
  return obs;
}

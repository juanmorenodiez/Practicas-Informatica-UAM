/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include "tiempos.h"
#include "ordenacion.h"
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>

/***********************************************************/
/* Funcion: tiempo_medio_ordenación Fecha: 23/10/2018      */
/* Autores: Juan Moreno y Andrés Mena                      */
/*                                                         */
/* Función que rellena los campos de la estructura         */
/* PTIEMPO y mediante un clock, mide el tiempo que         */
/* tardará en ordenar una tabla que contiene n_perms       */
/* permutaciones y cada permutación N elementos. Se busca  */
/* tambien cual es la permutacion que realiza más ob       */
/* y la que menos.                                         */
/*                                                         */
/* Entrada:                                                */
/* pfunc_ordena metodo: puntero a la función de ordenación */
/* int n_perms: numero de permutaciones                    */
/* int N: número de elementos de la permutación            */
/* PTIEMPO ptiempo: puntero a la estructura PTIEMPO        */
/* Salida:                                                 */
/* short: devuelve ERR en caso de error o OK en el         */
/* caso de que las tablas se ordenen correctamente         */
/***********************************************************/

short tiempo_medio_ordenacion(pfunc_ordena metodo,
                              int n_perms,
                              int N,
                              PTIEMPO ptiempo)
{
  int i;
  double start, end;

  int **perms = genera_permutaciones(n_perms, N);
  if(perms == NULL)
    return ERR;

  ptiempo->medio_ob = 0;
  ptiempo->max_ob = 0;
  ptiempo->min_ob = INT_MAX;

  start=clock();
  for (i=0; i<n_perms; i++){
    int obt = metodo(perms[i], 0, N-1);

    ptiempo->medio_ob+=obt;
    if (obt>ptiempo->max_ob)
      ptiempo->max_ob = obt;
    if (obt<ptiempo->min_ob)
      ptiempo->min_ob = obt;
  }
  end=clock();
  ptiempo->medio_ob = (double)(ptiempo->medio_ob/n_perms);
  ptiempo->tiempo = (double)((end-start)/n_perms/CLOCKS_PER_SEC);
  ptiempo->N = N;
  ptiempo->n_elems = n_perms;



  return OK;
}

/***********************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha: 23/10/2018    */
/* Autores: Juan Moreno y Andrés Mena                      */
/*                                                         */
/* Se reserva memoria para rellenar el número de           */
/* estructuras de tiempo que vamos a necesitar, dependiendo*/
/* de los parametros num_min, num_max e incr. y luego se   */
/* realizan llamadas a la función tiempo_medio_ordenacion  */
/* para llenar todas las posiciones de nuestro array de    */
/* tiempo. Una vez finalizado esto, llamamos a la función  */
/* guarda_tabla_tiempos para introducir estos datos en un  */
/* fichero.                                                */
/*                                                         */
/* Entrada:                                                */
/* pfunc_ordena metodo: puntero a la función de ordenación */
/* char *fichero: fichero en el que se escribirán los      */
/* tiempos medio, números promedio, mínimo y máximo        */
/* número de veces que se ejectuta la OB                   */
/* int num_min: tamaño mínimo de la permutación            */
/* int num_max: tamaño máximo de la permutación            */
/* int incr: tamaño del increment                          */
/* int n_perms: número de permutaciones                    */
/* Salida:                                                 */
/* short: devuelve ERR en caso de error o OK en el caso    */
/* contrario                                               */
/***********************************************************/

short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_perms)
{
	PTIEMPO ptiempo;
	int j, i;
	for (j=num_min, i=0  ; j<=num_max ; j+=incr, i++);

	ptiempo=(PTIEMPO) malloc ((i-1) * sizeof(ptiempo[0]));
	if (ptiempo==NULL)
		return ERR;



	for (j=num_min, i=0  ; j<=num_max ; j+=incr, i++){
		if (tiempo_medio_ordenacion (metodo, n_perms, j, &ptiempo[i])==ERR){
      free (ptiempo);
      return ERR;
    }
  }

	if (guarda_tabla_tiempos(fichero, ptiempo, i-1)==ERR){
      free (ptiempo);
      return ERR;
    }
	return OK;
}

/***********************************************************/
/* Funcion: guarda_tabla_tiempos Fecha: 24/10/2018         */
/* Autores: Juan Moreno y Andrés Mena                      */
/*                                                         */
/* Función que genera un fichero el cual guarda los        */
/* tiempos medio, números promedio, mínimo y máximo        */
/* número de veces que se ejecuta la OB                    */
/*                                                         */
/* Entrada:                                                */
/* char *fichero: fichero en el que se escribirán los      */
/* tiempos medio, números promedio, mínimo y máximo        */
/* número de veces que se ejectuta la OB                   */
/* PTIEMPO ptiempo: puntero a la estructura PTIEMPO        */
/* int n_tiempos: número de elementos del array tiempo     */
/* Salida:                                                 */
/* short: devuelve ERR en caso de error o OK en el         */
/* caso contrario                                          */
/***********************************************************/

short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
	FILE *f;
	int i;

	f = fopen (fichero, "w");
	if (f==NULL)
		return ERR;

	for (i=0; i<n_tiempos; i++)
	 fprintf (f, "%d\t%f\t%f\t%d\t%d\n", tiempo[i].N, tiempo[i].tiempo, tiempo[i].medio_ob, tiempo[i].max_ob, tiempo[i].min_ob);

  fclose (f);
	return OK;
}

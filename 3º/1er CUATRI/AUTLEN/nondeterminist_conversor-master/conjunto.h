#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <stdio.h>
#include <stdlib.h>

/**
  * Struct 
  * 
  * Representa un conjunto de estados
  */
typedef struct _conjunto conjunto;

/**
  * Crea un nuevo conjunto a partir de un array de estados, 
  * no necesita la cantidad de estados (acaba en -1)
  * 
  * @param estados el array de estados
  * 
  * @return La nueva estructura tipo conjunto
  */

conjunto *new_conjunto(int *estados);

/**
  * libera un conjunto
  * 
  * @param conjunto el conjunto a liberar
  */
void free_conjunto(conjunto *conjunto);

/**
  * Obtiene la cantidad de un conjunto
  * 
  * @param conjunto del que queremos conocer la cantidad
  * 
  * @return la cantidad de estados del conjunto
  */
int conjunto_get_cantidad(conjunto *conjunto);

/**
  * Obtiene los estados de un conjunto
  * 
  * @param conjunto del que queremos conocer los estados
  * 
  * @return es array de estados del conjunto
  */
int *conjunto_get_estados(conjunto *conjunto);

/**
  * Cambia el conjunto de estados de un conjunto
  * 
  * @param conjunto el conjunto a modificar
  * @param nuevos_estados el nuevo array de estados del conjunto
  */
void conjunto_set_estados(conjunto *conjunto, int *nuevos_estados);

/**
  * Cambia el valor de cantidad de una estructura de conjuntos
  * 
  * @param conjunto el conjunto a modificar
  * @param nueva_cantidad la nueva cantidad que se le asignara
  */

void conjunto_set_cantidad(conjunto *conjunto, int nueva_cantidad);

/**
  * Elimina un estado de la estructura de conjuntos
  * 
  * @param conjunto el conjunto a modificar
  * @param el estado que vamos a eliminar del conjunto
  *         (suponemos que se encuentra en el conjunto)
  */
void conjunto_eliminar_estado(conjunto *conjunto, int estado);

/**
  * Le añade un estado al subconjunto
  * 
  * @param conjunto el conjunto a modificar
  * @param el estado que vamos a añadir al conjunto
  */
void conjunto_add_estado(conjunto *conjunto, int new_estado);

#endif
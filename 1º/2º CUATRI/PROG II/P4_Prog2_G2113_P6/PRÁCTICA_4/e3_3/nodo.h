/** 
 * @brief Define la interfaz de nodo.c
 * for each command
 * 
 * @file nodo.h
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0 
 * @date 12-03-2018 
 * @copyright GNU Public License
 */
#ifndef NODO_H
#define NODO_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef enum {
	BLANCO, NEGRO
} Label;

typedef struct _Node Node;

/* Inicializa un nodo, reservando memoria y devolviendo el nodo inicializado si
* lo ha hecho correctamente, sino devuelve NULL en otro caso
* e imprime el string correspondiente al errorno en stderror */
Node * node_ini();

/* Libera la memoria dinámica reservada para un nodo */
void node_destroy(Node * n);

/* Devuelve el id de un nodo dado, o -1 en caso de error */
int node_getId(const Node * n);

/* Devuelve un puntero al nombre de un nodo dado, o NULL en caso de error */
const char* node_getName(const Node * n);

/* Modifica el id de un nodo dado, devuelve NULL en caso de error */
Node * node_setId(Node * n, const int id);

/* Modifica el nombre de un nodo dado, devuelve NULL en caso de error */
Node * node_setName(Node * n, char* name);

/* Compara dos nodos por el id y después el nombre.
* Devuelve 0 cuando ambos nodos tienen el mismo id, un número menor que
* 0 cuando n1 < n2 o uno mayor que 0 en caso contrario. */
int node_cmp (const Node * n1, const Node * n2);

/* Reserva memoria para un nodo en el que copia los datos del nodo src.
* Devuelve la dirección del nodo copia si todo ha ido bien, o NULL en otro caso
*/
Node * node_copy(const Node * src);

/* Imprime en pf los datos de un nodo con el formato: [id, name, nConnect]
* Devuelve el número de caracteres que se han escrito con éxito.
* Comprueba si ha habido errores en el flujo de salida, en ese caso imprime
* mensaje de error en stderror*/
int node_print(FILE *pf, const Node *n);

#endif /* NODE_H_ */
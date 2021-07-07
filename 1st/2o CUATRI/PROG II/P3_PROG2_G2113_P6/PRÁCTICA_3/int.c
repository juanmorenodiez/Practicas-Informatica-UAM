/**
 * @brief Define el TAD INT(trabaja con enteros)
 *
 * @file int.c
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0
 * @date 15-04-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "int.h"

/**
* @brief Crea e inicializa un entero.
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param
* @return int* pi
*/

int* int_ini(){
	int* pi = NULL;

	pi = (int*) malloc (sizeof(int));

	if(!pi){
		return NULL;
	}

	return pi;
}

/**
* @brief Destruye el entero
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param int* dato
* @return
*/

void int_destroy(int* dato){
	if(!dato){
		return;
	}

	free(dato);
	return;
}

/**
* @brief hace una copia de un entero
* reservando memoria para el
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param int* dato
* @return int* copia
*/

int* int_copy(int* dato){
	int* copia = NULL;

	copia = int_ini();

	if(!copia){
		return NULL;
	}

	*copia = *dato;

	return copia;
}

/**
* @brief realiza una comparacion entre
* dos enteros dados
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param int* dato1
* @param int* dato2
* @return int
*/

int int_cmp(int* dato1, int* dato2){
	if(!dato1 || !dato2){
		return -99;
	}

	if(*dato1 == *dato2){
		return 0;
	}else if(*dato1 > *dato2){
		return 1;
	}else{
		return -1;
	}
}

/**
* @brief imprime el valor de un entero
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param FILE* pf
* @param int* dato
* @return bytes, numero de caracteres
*/

int int_print(FILE* pf, int* dato){
	int bytes = 0;
	if(!pf || !dato){
		return -1;
	}

	bytes = fprintf(pf, "%d ", *(int*)dato);

	return bytes;
}

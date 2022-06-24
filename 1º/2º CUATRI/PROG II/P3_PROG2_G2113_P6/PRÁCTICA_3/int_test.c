/**
 * @brief test para comprobar el funcionamiento
 * del tad INT
 *
 * @file int_test.c
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0
 * @date 15-04-2019
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "int.h"

int main(){
	int *numero1 = NULL, *copia = NULL;

	numero1 = int_ini();
	fprintf(stdout, "Introduzca un entero\n");
	scanf("%d", numero1);

	copia = int_copy(numero1);

	int_print(stdout, numero1);

	printf("\n");

	int_print(stdout, copia);

	printf("\n");

	int_destroy(numero1);

	int_destroy(copia);

	return 0;
}

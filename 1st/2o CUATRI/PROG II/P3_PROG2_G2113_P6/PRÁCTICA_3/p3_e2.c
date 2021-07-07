#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "list.h"
#include "int.h"

int main(int args, char* argv[]){
	void *ele1 = NULL, *ele2 = NULL;
	int i = 0, j = 0;
	int numero;
	List* lista1 = NULL;
	List* lista2 = NULL;

	if(args < 2){
		fprintf(stdout, "La sintaxis correcta es: %s < numero entero >", argv[0]);
		return 1;
	}

	lista1 = list_ini((destroy_element_function_type) int_destroy, (copy_element_function_type) int_copy, (print_element_function_type) int_print, (cmp_element_function_type) int_cmp);

	if(!lista1){
		return 1;
	}

	lista2 = list_ini((destroy_element_function_type) int_destroy, (copy_element_function_type) int_copy, (print_element_function_type) int_print, (cmp_element_function_type) int_cmp);

	if(!lista2){
		list_destroy(lista1);
		return 1;
	}

	numero = atoi(argv[1]);

	for(i = numero; i >= 1 ; i--){
		if (i % 2 == 0) {
			list_insertFirst(lista1, &i);
		}
		else
			list_insertLast(lista1, &i);

		list_insertInOrder(lista2, &i);
	}

	printf("Lista 1\n");
	list_print(stdout, lista1);
	printf("\n");
	printf("Lista 2\n");
	list_print(stdout, lista2);
	printf("\n");

	printf("------------------Vaciando lista 1------------------\n");

	while (list_isEmpty(lista1) == FALSE) {
		ele1 = list_extractFirst(lista1);
		j++;
		printf("%da extracción:", j);
		int_print(stdout, (void*) ele1);
		int_destroy(ele1);
		printf("\n");
	}

	if (list_print(stdout, lista1) == 0) {
		printf("Lista 1 vacía, se han extraído correctamente todos los elementos.\n");
	}

	j = 0;

	printf("------------------Vaciando lista 2------------------\n");

	while (list_isEmpty(lista2) == FALSE) {
		ele2 = list_extractFirst(lista2);
		j++;
		printf("%da extracción:", j);
		int_print(stdout, (void*) ele2);
		int_destroy(ele2);
		printf("\n");
	}

	if (list_print(stdout, lista2) == 0) {
		printf("Lista 2 vacía, se han extraído correctamente todos los elementos.\n");
	}

	list_destroy(lista1);
	list_destroy(lista2);

	return 0;
}

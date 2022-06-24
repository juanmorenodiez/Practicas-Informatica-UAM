#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "int.h"

int* int_ini(){
	int* pi = NULL;

	pi = (int*) malloc (sizeof(int));

	if(!pi){
		return NULL;
	}

	return pi;
}

void int_destroy(int* dato){
	if(!dato){
		return;
	}

	free(dato);
	return;
}

int* int_copy(int* dato){
	int* copia = NULL;

	copia = int_ini();

	if(!copia){
		return NULL;
	}

	*copia = *dato;

	return copia;
}

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

int int_print(FILE* pf, int* dato){
	int bytes = 0;
	if(!pf || !dato){
		return -1;
	}

	bytes += fprintf(pf, "%d ", *(int*)dato);

	return bytes;
}

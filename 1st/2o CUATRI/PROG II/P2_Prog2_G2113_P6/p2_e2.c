#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack_elestack.h"
#include "elestack.h"

int main(int argc, char *argv[]){
	EleStack* eles = NULL;
	Stack* s = NULL;
	int i=0;

	/* COMPROBACIÓN DEL NÚMERO DE ARGUMENTOS */
	if(argc < 2){
		fprintf(stdout, "ERROR: La sintaxis correcta es %s <numero entero>.\n", argv[0]);
		return 1;
	}

	/* INICIALIZACIÓN DEL ELEMENTO */
	eles = EleStack_ini();

	if(!eles){
		return 1;
	}

	/* INICIALIZACIÓN DE LA PILA */
	s = stack_ini();

	if(!s){
		EleStack_destroy(eles);
		return 1;
	}

	/* IMPRIMIR POR PANTALLA EL CONTENIDO DE LA PILA ANTES DE LLAMAR A LA FUNCIÓN */
	fprintf(stdout, "Pila antes de la llamada a la función:\n");

	for(i=0 ; i < atoi(argv[1])+1 ; i++){
		EleStack_setInfo(eles, &i);
		stack_push(s, eles);
	}

	/* SE IMPRIME POR LA PANTALLA LA MEDIA DE LOS ELEMENTOS */
	fprintf(stdout, "La media es: %f \n", stack_media(s, argv));

	fprintf(stdout, "Pila después de la llamada a la función: ");

	for(i=0 ; i < atoi(argv[1])+1 ; i++){
		EleStack_setInfo(eles, &i);
		stack_push(s, eles);
	}

	/* LIBERACIÓN DE TODO EL ESPACIO RESERVADO EN EL PROGRAMA */
	EleStack_destroy(eles);

	stack_print(stdout, s);

	stack_destroy(s);

	return 0;

}	
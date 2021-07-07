#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "tree.h"
#include "cad.h"

#define WORD_SIZE 32
int main(int argc, char* argv[]){
	FILE* file = NULL;
	Tree* tree = NULL;
	char line[WORD_SIZE] = " ";
	char* toks = NULL;
	int numnodes, prof;
	char cadena[WORD_SIZE];

	if(argc < 2){
		fprintf(stderr, "Sintaxis: La sintaxis correcta es: %s < fichero.txt >\n", argv[0]);
		return 1;
	}

	file = fopen(argv[1], "r");

	if(!file){
		fprintf(stderr, "Error en la apertura de %s\n", argv[1]);
	}

	tree = tree_ini((destroy_elementtree_function_type) cadena_free, (copy_elementtree_function_type) cadena_copy,(print_elementtree_function_type) cadena_print, (cmp_elementtree_function_type) cadena_cmp);

	if(!tree){
		fprintf(stderr, "Error al iniciar el árbol.\n");
		fclose(file);
		return 1;
	}

	while(fgets(line, WORD_SIZE, file)){
		toks = strtok(line, "\n");
		if (tree_insert(tree, toks) == ERROR) {
			printf("Error introduciendo el elemento en el arbol\n");
			fclose(file);
			tree_free(tree);
		}
	}

	numnodes = tree_numNodes(tree);
	if (numnodes == -1) {
		fclose(file);
		tree_free(tree);
		return -1;
	}

	printf("Número de nodos: %d\n", numnodes);

	prof = tree_depth(tree);
	if (prof == -1) {
		fclose(file);
		tree_free(tree);
		return -1;
	}

	printf("Profundidad: %d\n", prof);

	printf("Orden medio: ");
	tree_inOrder(stdout, tree);

  	printf("\n");

	printf("> Introduce una cadena para buscar en el arbol: ");
	scanf("%s", cadena);
	printf("%s\n", cadena);

	if (tree_find(tree, cadena) == TRUE) {
		printf("Elemento encontrado!\n");
	}

	else {
		printf("Elemento no encontrado...\n");
	}

	fclose(file);
	tree_free(tree);

	return 0;
}

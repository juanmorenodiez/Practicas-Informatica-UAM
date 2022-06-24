#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "tree.h"
#include "int.h"

#define WORD_SIZE 32
int main(int argc, char* argv[]){
	FILE* file = NULL;
	Tree* tree = NULL;
	char line[WORD_SIZE] = " ";
	char* toks = NULL;
	int numnodes, prof;
	int numero, aux;

	if(argc < 2){
		fprintf(stderr, "Sintaxis: La sintaxis correcta es: %s < fichero.txt >\n", argv[0]);
		return 1;
	}

	file = fopen(argv[1], "r");

	if(!file){
		fprintf(stderr, "Error en la apertura de %s\n", argv[1]);
	}

	tree = tree_ini((destroy_elementtree_function_type) int_destroy, (copy_elementtree_function_type) int_copy,(print_elementtree_function_type) int_print, (cmp_elementtree_function_type) int_cmp);

	if(!tree){
		fprintf(stderr, "Error al iniciar el árbol.\n");
		fclose(file);
		return 1;
	}

	while(fgets(line, WORD_SIZE, file)){
		toks = strtok(line, " ");
		aux = atoi(toks);
		if (tree_insert(tree, &aux) == ERROR) {
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

	printf("Orden previo: ");
	tree_preOrder(stdout, tree);

	printf("\n");

	printf("Orden medio: ");
	tree_inOrder(stdout, tree);

	printf("\n");

	printf("Orden posterior: ");
	tree_postOrder(stdout, tree);

	printf("\n");

	printf("> Introduzca un numero: ");
	scanf("%d", &numero);
	printf("Número introducido: %d\n", numero);

	if (tree_find(tree, &numero) == TRUE) {
		printf("El dato %d se encuentra dentro del Árbol. \n", numero);
	}

	else {
		printf("El dato %d no se encuentra dentro del Árbol. \n", numero);
	}

	fclose(file);
	tree_free(tree);

	return 0;
}

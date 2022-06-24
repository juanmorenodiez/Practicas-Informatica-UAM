#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "tree.h"
#include "nodo.h"

#define WORD_SIZE 32
int main(int argc, char* argv[]){
	FILE* file = NULL;
	Tree* tree = NULL;
	Node* node = NULL;
	char line[WORD_SIZE] = " ";
	char* toks = NULL;
	int numnodes, prof;
	char* node_name = NULL;
	int node_id = 0;

	if(argc < 2){
		fprintf(stderr, "Sintaxis: La sintaxis correcta es: %s < fichero.txt >\n", argv[0]);
		return 1;
	}

	file = fopen(argv[1], "r");

	if(!file){
		fprintf(stderr, "Error en la apertura de %s\n", argv[1]);
	}

	tree = tree_ini((destroy_elementtree_function_type) node_destroy, (copy_elementtree_function_type) node_copy, (print_elementtree_function_type) node_print, (cmp_elementtree_function_type) node_cmp);

	if(!tree){
		fprintf(stderr, "Error al iniciar el árbol.\n");
		fclose(file);
		return 1;
	}

	node = node_ini();

	if(!node){
		fprintf(stderr, "Error al iniciar el nodo.\n");
		fclose(file);
		tree_free(tree);
		return 1;
	}

	while(fgets(line, WORD_SIZE, file)){
		toks = strtok(line, " ");
		node_id = atoi(toks);
		node_name = strtok(NULL, "\n");
			

		node_setName(node, node_name);
		node_setId(node, node_id);

		if (tree_insert(tree, node) == ERROR) {
			printf("Error introduciendo el elemento en el arbol\n");
			fclose(file);
			tree_free(tree);
		}
	}

	numnodes = tree_numNodes(tree);

	if (numnodes == -1) {
		tree_free(tree);
		fclose(file);
		return -1;
	}

	printf("\nNúmero de nodos: %d\n", numnodes);

	prof = tree_depth(tree);

	if (prof == -1) {
		tree_free(tree);
		fclose(file);
		return -1;
	}

	printf("Profundidad: %d\n", prof);

	fprintf(stdout, "Orden previo: ");
	tree_preOrder(stdout, tree);
	fprintf(stdout, "\n");

	fprintf(stdout, "Orden medio: ");
	tree_inOrder(stdout, tree);
	fprintf(stdout, "\n");

	fprintf(stdout, "Orden posterior: ");
	tree_postOrder(stdout, tree);
	fprintf(stdout, "\n");

	fclose(file);
	tree_free(tree);
	node_destroy(node);

	return 0;
}
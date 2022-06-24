#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodo.h"
int main(int argc, char *argv[]){
	Node* n1;
	Node* n2;

	n1 = node_ini();

	n1 = node_setId(n1, 111);
	n1 = node_setName(n1, "first");

	n2 = node_ini();

	n2 = node_setId(n2, 222);
	n2 = node_setName(n2, "second");

	node_print(stdout, n1);
	node_print(stdout, n2);

	fprintf(stdout, "\n");

	fprintf(stdout, "¿Son iguales?");

	if(node_cmp(n1,n2) == 0)
		fprintf(stdout, "Sí\n");

	else
		fprintf(stdout, "No\n");

	fprintf(stdout, "Id del primer nodo: %d\n", node_getId(n1));
	fprintf(stdout, "Nombre del segundo nodo es: %s", node_getName(n2));

	node_destroy(n2);

	n2 = node_copy(n1);

	fprintf(stdout, "\n");

	node_print(stdout, n1);
	node_print(stdout, n2);

	fprintf(stdout, "\n");

	fprintf(stdout, "¿Son iguales?");

	if(node_cmp(n1,n2) == 0)
		fprintf(stdout, "Sí\n");

	else
		fprintf(stdout, "No\n");

	node_destroy(n1);

	node_destroy(n2);

	return 0;
}

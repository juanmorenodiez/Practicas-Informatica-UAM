#ifndef TREE_H
#define TREE_H

#include "types.h"
#include "nodo.h"

typedef struct _Tree Tree;

typedef void (*destroy_elementtree_function_type)(void*);
typedef void (*(*copy_elementtree_function_type)(const void*));
typedef int (*print_elementtree_function_type)(FILE *, const void*);
typedef int (*cmp_elementtree_function_type)(const void*, const void*);

/* Inicializa un Arbol vacio. */
Tree* tree_ini(destroy_elementtree_function_type f1, copy_elementtree_function_type f2, print_elementtree_function_type f3, cmp_elementtree_function_type f4);

/* Indica si el Arbol esta o no vacio. */
Bool tree_isEmpty( const Tree *pa);

/* Libera la memoria utilizada por un Arbol. */
void tree_free(Tree *pa);

/* Inserta un elemento en un Arbol binario de busqueda copiándolo en memoria nueva. */
Status tree_insert(Tree *pa, const void *po);

/* Escribe en el fichero f el recorrido de un Arbol en orden previo sin modificarlo. */
Status tree_preOrder(FILE *f, const Tree *pa);

/* Escribe en el fichero f el recorrido de un Arbol en orden medio sin modificarlo. */
Status tree_inOrder(FILE *f, const Tree *pa);

/* Escribe en el fichero f el recorrido de un Arbol en post orden sin modificarlo. */
Status tree_postOrder(FILE *f, const Tree *pa);

/* Calcula la profundidad de un Arbol. Un Arbol vacio tiene profundidad -1. */
int tree_depth(const Tree *pa);

/* Calcula el numero de nodos de un Arbol. Un Arbol vacio tiene 0 nodos. */
int tree_numNodes(const Tree *pa);

/* Devuelve TRUE si se puede encontrar el elemento pe en el árbol pa */
Bool tree_find(Tree* pa, const void* pe);

#endif

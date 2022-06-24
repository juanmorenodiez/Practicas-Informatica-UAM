#ifndef LIST_H
#define LIST_H

#include "nodo.h"
#include "types.h"

typedef struct _List List;

/* Tipos de los punteros a función soportados por la lista. Nota: podrían estar en elem_functions.h e incluirlo aquí */
typedef void (*destroy_element_function_type)(void*);
typedef void *(*copy_element_function_type)(const void*);
typedef int (*print_element_function_type)(FILE *, const void*);
typedef int (*cmp_element_function_type)(const void*, const void*);

/*El último tipo de funciones, cmp, serán aquellas que sirvan para comparar dos elementos, devolviendo un número
positivo, negativo o cero según sea el primer argumento mayor, menor o igual que el segundo */
/* Inicializa la lista reservando memoria e inicializa todos sus elementos. */
List* list_ini (destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4);

/* Libera la lista, liberando todos sus elementos. */
void list_destroy (List* list);

/* Inserta al principio de la lista realizando una copia de la información recibida. */
Status list_insertFirst (List* list, const void *pelem);

/* Inserta al final de la lista realizando una copia de la información recibida. */
Status list_insertLast (List* list, const void *pelem);

/* Inserta en orden en la lista realizando una copia del elemento. */
Status list_insertInOrder (List *list, const void *pelem);

/* Extrae del principio de la lista, devolviendo directamente el puntero al campo info del nodo extraído, nodo que finalmente
es liberado. OJO: tras guardar la dirección del campo info que se va a devolver y antes de liberar el nodo, pone el campo
info del nodo a NULL, para que no siga apuntando a la info a devolver y, por tanto, no la libere al liberar el nodo */
void * list_extractFirst (List* list);

/* Extrae del final de la lista, devolviendo directamente el puntero al campo info del nodo extraído, nodo que finalmente es
liberado. OJO: tras guardar la dirección del campo info que se va a devolver y antes de liberar el nodo, pone el campo info
del nodo a NULL, para que no siga apuntando a la info a devolver y, por tanto, no la libere al liberar el nodo */
void * list_extractLast (List* list);

/* Comprueba si una lista está vacía o no. */
Bool list_isEmpty (const List* list);

/* Devuelve la información almacenada en el nodo i-ésimo de la lista. En caso de error, devuelve NULL. */
const void* list_get (const List* list, int index);

/* Devuelve el número de elementos que hay en una lista. */
int list_size (const List* list);

/* Imprime una lista devolviendo el número de caracteres escritos. */
int list_print (FILE *fd, const List* list);

#endif
 #ifndef _ALFA_H_

#define _ALFA_H_
#include "hash.h"
#include "tablaSimbolos.h"
#include "generacion.h"
#define MAX_LONG 100
#define MAX_TAMANIO_VECTOR 64
#define ERR_OUT stdout
struct _tipo_atributos {
	char nombre[MAX_LONG + 1];
	int tipo;
	int valor_numerico;
	int etiqueta;
	int es_direccion;
};
typedef struct _tipo_atributos tipo_atributos;

#endif
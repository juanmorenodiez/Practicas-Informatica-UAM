#ifndef HASH_H
#define HASH_H

#include <stdio.h>

#define POS_INI_PARAMS 0      
#define POS_INI_VARS_LOCALES 1  

#define HASH_INI 3412
#define HASH_FACTOR 27 

typedef enum { ERR = 0, OK = 1 } STATUS;

typedef enum { VARIABLE, PARAMETRO, FUNCION } CATEGORIA;

typedef enum { ENTERO, BOOLEANO } TIPO;

typedef enum { ESCALAR, VECTOR } CLASE;

typedef struct {
    char *lexema;           
    CATEGORIA categoria;       
    TIPO tipo;              
    CLASE clase;           
    int adicional1;
    int adicional2;   
} INFO_SIMBOLO;

typedef struct nodo_hash {
    INFO_SIMBOLO *info;      
    struct nodo_hash *siguiente;   
} NODO_HASH;

typedef struct {
    int tam;            
    NODO_HASH **tabla;  
} TABLA_HASH;

INFO_SIMBOLO *crear_info_simbolo(const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int adic1, int adic2);
void liberar_info_simbolo(INFO_SIMBOLO *is);
NODO_HASH *crear_nodo(INFO_SIMBOLO *is);
void liberar_nodo(NODO_HASH *nh);
TABLA_HASH *crear_tabla(int tam);
void liberar_tabla(TABLA_HASH *th);
unsigned long hash(const char *str);
INFO_SIMBOLO *buscar_simbolo(const TABLA_HASH *th, const char *lexema);
STATUS insertar_simbolo(TABLA_HASH *th, const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int adic1, int adic2);
void borrar_simbolo(TABLA_HASH *th, const char *lexema);

#endif 

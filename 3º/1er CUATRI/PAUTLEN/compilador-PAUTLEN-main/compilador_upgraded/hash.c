#include <stdlib.h>
#include <string.h>
#include "hash.h"

INFO_SIMBOLO *crear_info_simbolo(const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int adic1, int adic2) {
    INFO_SIMBOLO *is;

    is = (INFO_SIMBOLO *) malloc(sizeof(INFO_SIMBOLO));

    if (is == NULL) { 
        return NULL;
    }

    if ((is->lexema = strdup(lexema)) == NULL) {
        free(is);
        return NULL;
    }

    is->categoria = categ;
    is->tipo = tipo;
    is->clase = clase;
    is->adicional1 = adic1;
    is->adicional2 = adic2;
    
    return is;
}

void liberar_info_simbolo(INFO_SIMBOLO *is) {
    if (is != NULL) {
        if (is->lexema != NULL) {
            free(is->lexema);
        }
        free(is);
    }
    return;
}

NODO_HASH *crear_nh(INFO_SIMBOLO *is) {
    NODO_HASH *nh;

    nh = (NODO_HASH *) malloc(sizeof(NODO_HASH));

    if (nh == NULL) {
        return NULL;
    }

    nh->info = is;
    nh->siguiente = NULL;

    return nh;
}

void liberar_nh(NODO_HASH *nh) {
    if (nh) {
        liberar_info_simbolo(nh->info);
        free(nh);
    }
}

TABLA_HASH *crear_tabla(int tam) {
    TABLA_HASH *th;

    th = (TABLA_HASH*) malloc(sizeof(TABLA_HASH));

    if (th == NULL) {
        return NULL;
    }

    th->tabla = (NODO_HASH **) calloc(tam, sizeof(NODO_HASH *));

    if (th->tabla == NULL) {
        free(th);
        return NULL;
    }

    th->tam = tam;
    
    return th;
}

void liberar_tabla(TABLA_HASH *th) {
    int i;
    NODO_HASH *node1, *node2;
    
    if (th != NULL) {
        if (th->tabla != NULL) {
            for (i = 0; i < th->tam; i++) {
                node1 = th->tabla[i];
                while (node1 != NULL) {
                    node2 = node1->siguiente;
                    liberar_nh(node1);
                    node1 = node2;      
                }
            }
            free(th->tabla);
        }
        free(th);
    }
}

unsigned long hash(const char *str) {
    unsigned long h = HASH_INI;
    unsigned char *p;

    for (p = (unsigned char *) str; *p; p++) {
        h = h*HASH_FACTOR + *p;
    }

    return h;
}

INFO_SIMBOLO *buscar_simbolo(const TABLA_HASH *th, const char *lexema) {
    unsigned int ind;    
    NODO_HASH *nh;
        
    ind = hash(lexema) % th->tam;
    nh = th->tabla[ind];

    while (nh != NULL && (nh->info == NULL || strcmp(nh->info->lexema, lexema))) {
        nh = nh->siguiente;
    }

    if(nh == NULL) {
        return NULL;
    }

    return nh->info;
}

STATUS insertar_simbolo(TABLA_HASH *th, const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int adic1, int adic2) {
    int ind;
    INFO_SIMBOLO *is;    
    NODO_HASH *nh = NULL;
    
    if (buscar_simbolo(th, lexema)) {
        return ERR;
    }

    ind = hash(lexema) % th->tam;

    if (!(is = crear_info_simbolo(lexema, categ, tipo, clase, adic1, adic2))) {
        return ERR;
    }

    if (!(nh = crear_nh(is))) {
        liberar_info_simbolo(is);
        return ERR;
    }
    
    nh->siguiente = th->tabla[ind];
    th->tabla[ind] = nh;

    return OK;
}

void borrar_simbolo(TABLA_HASH *th, const char *lexema) {
    int ind;
    NODO_HASH *nh, *prev = NULL;

    ind = hash(lexema) % th->tam;
    nh = th->tabla[ind];

    while (nh != NULL && (nh->info == NULL || strcmp(nh->info->lexema, lexema))) {
        prev = nh;
        nh = nh->siguiente;
    }

    if (nh == NULL) {
        return;
    } 

    if (prev == NULL) {
        th->tabla[ind] = nh->siguiente;
    }

    else {
        prev->siguiente = nh->siguiente;
    }

    liberar_nh(nh);
    return;
}
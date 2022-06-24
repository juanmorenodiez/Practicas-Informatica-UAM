#include <stdio.h>
#include "tablaSimbolos.h"

TABLA_HASH *TablaSimbolosGlobal = NULL;
TABLA_HASH *TablaSimbolosLocal = NULL;

STATUS Declarar(const char *id, INFO_SIMBOLO *desc_id) {
    if(TablaSimbolosLocal == NULL){
        return DeclararGlobal(id, desc_id);
    }

    return DeclararLocal(id, desc_id);
}

STATUS DeclararGlobal(const char *id, INFO_SIMBOLO *desc_id) {
    if(TablaSimbolosGlobal == NULL) {
        TablaSimbolosGlobal = crear_tabla(TABLA_SIMBOLOS_GLOBAL_TAM);
        if(TablaSimbolosGlobal == NULL) {
            return ERR;
        }
    }
    if(buscar_simbolo(TablaSimbolosGlobal, id) == NULL) {
        return insertar_simbolo(TablaSimbolosGlobal, id, desc_id->categoria, desc_id->tipo, desc_id->clase, desc_id->adicional1, desc_id->adicional2);
    }
    return ERR;
}

STATUS DeclararLocal(const char *id, INFO_SIMBOLO *desc_id) {
    if(buscar_simbolo(TablaSimbolosLocal, id) == NULL) {
        return insertar_simbolo(TablaSimbolosLocal, id, desc_id->categoria, desc_id->tipo, desc_id->clase, desc_id->adicional1, desc_id->adicional2);
    }
    return ERR;
}

INFO_SIMBOLO *UsoGlobal(const char *id) {
    if(TablaSimbolosGlobal == NULL) {
        return NULL;
    }
    return buscar_simbolo(TablaSimbolosGlobal, id);
}

INFO_SIMBOLO *UsoLocal(const char *id) {
    INFO_SIMBOLO *dato;
    if(TablaSimbolosLocal == NULL) {
        return UsoGlobal(id);
    }
    dato = buscar_simbolo(TablaSimbolosLocal, id);
    if(dato == NULL){
        return UsoGlobal(id);
    }
    return dato;
}

int EsLocal(const char *id) {
    if(TablaSimbolosLocal == NULL) {
        return 0;
    }
    return buscar_simbolo(TablaSimbolosLocal, id)!=NULL;

}

STATUS DeclararFuncion(const char *id, INFO_SIMBOLO *desc_id) {
    if(buscar_simbolo(TablaSimbolosGlobal, id) == NULL) {
        if(insertar_simbolo(TablaSimbolosGlobal, id, desc_id->categoria, desc_id->tipo, desc_id->clase, desc_id->adicional1, desc_id->adicional2) == ERR) {
            return ERR;
        }
        liberar_tabla(TablaSimbolosLocal);
        TablaSimbolosLocal = crear_tabla(TABLA_SIMBOLOS_LOCAL_TAM);
        if(TablaSimbolosLocal == NULL) {
            borrar_simbolo(TablaSimbolosGlobal, id);
            liberar_tabla(TablaSimbolosLocal);
            TablaSimbolosLocal = NULL;
            return ERR;
        }
        if(insertar_simbolo(TablaSimbolosLocal, id, desc_id->categoria, desc_id->tipo, desc_id->clase, desc_id->adicional1, desc_id->adicional2) == ERR) {
            borrar_simbolo(TablaSimbolosGlobal, id);
            liberar_tabla(TablaSimbolosLocal);
            TablaSimbolosLocal = NULL;
            return ERR;
        }
        return OK;
    }
    return ERR;
}

STATUS CerrarFuncion() {
    if(TablaSimbolosLocal == NULL) {
        return ERR;
    }
    liberar_tabla(TablaSimbolosLocal);
    TablaSimbolosLocal = NULL;
    return OK;
}

void Terminar() {
    if(TablaSimbolosLocal != NULL) {
        liberar_tabla(TablaSimbolosLocal);
    }
    if(TablaSimbolosGlobal != NULL) {
        liberar_tabla(TablaSimbolosGlobal);
    }
}
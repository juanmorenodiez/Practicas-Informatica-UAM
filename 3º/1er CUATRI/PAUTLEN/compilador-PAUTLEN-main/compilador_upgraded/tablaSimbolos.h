#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include "hash.h"

#define TABLA_SIMBOLOS_GLOBAL_TAM   65536
#define TABLA_SIMBOLOS_LOCAL_TAM    65536

STATUS Declarar(const char *id, INFO_SIMBOLO *desc_id);
STATUS DeclararGlobal(const char *id, INFO_SIMBOLO *desc_id);
STATUS DeclararLocal(const char *id, INFO_SIMBOLO *desc_id);
INFO_SIMBOLO *UsoGlobal(const char *id);
INFO_SIMBOLO *UsoLocal(const char *id);
int EsLocal(const char *id);
STATUS DeclararFuncion(const char *id, INFO_SIMBOLO *desc_id);
STATUS CerrarFuncion();
void Terminar();

#endif /* TABLASIMBOLOS_H */

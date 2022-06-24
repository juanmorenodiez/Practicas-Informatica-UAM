#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "estado.h"
#include "transformacion.h"

int main(int argc, char **argv)
{
    AFND *AFND, *determinista;
    AFND = AFNDNuevo("automata", 4, 2);

    /*Insertamos los simbolos*/
    AFNDInsertaSimbolo(AFND, "a");
    AFNDInsertaSimbolo(AFND, "b");

    /*Insertamos los estados*/
    AFNDInsertaEstado(AFND, "p", INICIAL_Y_FINAL);
    AFNDInsertaEstado(AFND, "q", NORMAL);
    AFNDInsertaEstado(AFND, "r", NORMAL);
    AFNDInsertaEstado(AFND, "s", FINAL);

    /*insertamos las transiciones normales*/
    AFNDInsertaTransicion(AFND, "p", "a", "q");
    AFNDInsertaTransicion(AFND, "q", "a", "p");
    AFNDInsertaTransicion(AFND, "q", "b", "p");
    AFNDInsertaTransicion(AFND, "q", "a", "r");
    AFNDInsertaTransicion(AFND, "q", "b", "r");
    AFNDInsertaTransicion(AFND, "q", "a", "s");
    AFNDInsertaTransicion(AFND, "r", "b", "p");
    AFNDInsertaTransicion(AFND, "r", "b", "s");

    /*Insertamos las transiciones lambda*/
    AFNDInsertaLTransicion(AFND, "q", "s");
    AFNDInsertaLTransicion(AFND, "r", "r");
    AFNDInsertaLTransicion(AFND, "r", "s");
    AFNDInsertaLTransicion(AFND, "s", "r");

    AFNDCierraLTransicion(AFND);
    AFNDImprimeConjuntoEstadosActual(stdout, AFND);

    determinista = AFND_convertir_a_determinista(AFND);

    AFNDADot(AFND);
    AFNDADot(determinista);

    /*transformacionEliminaLTransiciones(AFND);*/

    AFNDElimina(AFND);
    AFNDElimina(determinista);

    printf("CHECK FINAL\n");
    return 0;
}

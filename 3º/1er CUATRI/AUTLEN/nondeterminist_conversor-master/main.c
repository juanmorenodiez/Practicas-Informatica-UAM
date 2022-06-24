#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "transformacion.h"
#include "conjunto.h"

int main(int argc, char **argv)
{
    AFND *AFND, *determinista;
    AFND = AFNDNuevo("automata", 8, 2);
    int i, j;
    int *accesibles;
    int **matriz;
    int array[2];

    array[0] = 0;
    array[1] = -1;
    conjunto *conjunto_aux;

    conjunto_aux = new_conjunto(array);
    conjunto_add_estado(conjunto_aux, 1);
    conjunto_add_estado(conjunto_aux, 2);
    conjunto_add_estado(conjunto_aux, 3);
    conjunto_add_estado(conjunto_aux, 4);
    conjunto_add_estado(conjunto_aux, 5);
    conjunto_add_estado(conjunto_aux, 6);
    conjunto_add_estado(conjunto_aux, 7);

    /*Insertamos los simbolos*/
    AFNDInsertaSimbolo(AFND, "0");
    AFNDInsertaSimbolo(AFND, "1");

    /*Insertamos los estados*/
    AFNDInsertaEstado(AFND, "A", INICIAL);
    AFNDInsertaEstado(AFND, "B", NORMAL);
    AFNDInsertaEstado(AFND, "C", FINAL);
    AFNDInsertaEstado(AFND, "D", NORMAL);
    AFNDInsertaEstado(AFND, "E", NORMAL);
    AFNDInsertaEstado(AFND, "F", NORMAL);
    AFNDInsertaEstado(AFND, "G", NORMAL);
    AFNDInsertaEstado(AFND, "H", NORMAL);

    /*insertamos las transiciones normales*/
    AFNDInsertaTransicion(AFND, "A", "0", "B");
    AFNDInsertaTransicion(AFND, "A", "1", "F");
    AFNDInsertaTransicion(AFND, "B", "0", "G");
    AFNDInsertaTransicion(AFND, "B", "1", "C");
    AFNDInsertaTransicion(AFND, "C", "1", "C");
    AFNDInsertaTransicion(AFND, "C", "0", "A");
    AFNDInsertaTransicion(AFND, "D", "0", "C");
    AFNDInsertaTransicion(AFND, "D", "1", "G");
    AFNDInsertaTransicion(AFND, "E", "0", "H");
    AFNDInsertaTransicion(AFND, "E", "1", "F");
    AFNDInsertaTransicion(AFND, "F", "0", "C");
    AFNDInsertaTransicion(AFND, "F", "1", "G");
    AFNDInsertaTransicion(AFND, "G", "0", "G");
    AFNDInsertaTransicion(AFND, "G", "1", "E");
    AFNDInsertaTransicion(AFND, "H", "0", "G");
    AFNDInsertaTransicion(AFND, "H", "1", "C");

    /*Insertamos las transiciones lambda*/

    /*determinista = AFND_convertir_a_determinista(AFND);

    AFNDADot(AFND);*/

    determinista = minimizar_determinista(AFND);

    AFNDImprime(stdout, determinista);
    AFNDADot(determinista);

    AFNDElimina(AFND);
    AFNDElimina(determinista);

    free_conjunto(conjunto_aux);

    printf("CHECK FINAL\n");

    return 0;
}
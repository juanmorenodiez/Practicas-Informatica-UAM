#ifndef TRANSICION_H
#define TRANSICION_H

#include "afnd.h"

/**
  * Struct 
  * 
  * Representa un caso para la funcion de transicion
  */
typedef struct _transicion transicion;

/**
  * Crea un caso de la funcion de transicion
  * 
  * @param input_state Array del indice que tienen los estados en el AFND. Entrada
  * @param imput_symbol Indice del simbolo de entrada en el AFND
  * @param res_states Array del indice que tienen los estados en el AFND. Salida
  */
transicion *transicion_new(int *input_state, int input_symbol, int *output_states);

/**
  * Libera memoria de una transicion, con sus arrays incluidos
  * 
  * @param transicion, la transicion a liberar
  */

void transicion_free(transicion *transicion);

/**
  * Metodo getter del conjunto de estados de entrada del caso de la funcion de transicion.
  * 
  * @param El caso de la funcion de transicion
  * @return Array con el indice que ocupan los estados de entrada en el AFND
  */
int *transicion_get_input_states(transicion *transicion);

/**
  * Metodo getter del simbolo de entrada para el caso de la funcion de transicion.
  * 
  * @param El caso de la funcion de transicion
  * @return El indice que ocupa el simbolo de entrada
  */
int transicion_get_input_symbol(transicion *transicion);

/**
  * Metodo getter del conjunto de estados de salida del caso de la funcion de transicion.
  * 
  * @param El caso de la funcion de transicion
  * @return Array con el indice que ocupan los estados de salida en el AFND
  */
int *transicion_get_output_states(transicion *transicion);

char *transicion_get_input_state_name(AFND *AFND, transicion *transicion);

char *transicion_get_output_state_name(AFND *AFND, transicion *transicion);

int transicion_get_output_state_type(AFND *AFND, transicion *transicion);

int transicion_get_input_state_type(AFND *AFND, transicion *transicion);



void transicion_debug(AFND *AFND, transicion *transicion);

#endif

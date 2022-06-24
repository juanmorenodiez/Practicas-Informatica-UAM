#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transicion.h"
#include "afnd.h"

struct _transicion
{
  int *input_states;  /*Array de estados de entrada*/
  int input_symbol;   /*Simbolo de entrada*/
  int *output_states; /*Conjunto de estados a los que transiciona*/
};

transicion *transicion_new(int *input_states, int input_symbol, int *output_states)
{

  transicion *new_transicion;

  if (input_states == NULL || output_states == NULL)
    return NULL;

  new_transicion = (transicion *)malloc(sizeof(transicion));

  if (new_transicion == NULL)
    return NULL;

  new_transicion->input_states = input_states;
  new_transicion->input_symbol = input_symbol;
  new_transicion->output_states = output_states;

  return new_transicion;
}

void transicion_free(transicion *transicion)
{
  if (transicion == NULL)
  {
    return;
  }

  if (transicion->output_states != NULL && transicion->output_states != transicion->input_states)
  {
    free(transicion->output_states);
    transicion->output_states = NULL;
  }

  free(transicion);
  transicion = NULL;
}

int *transicion_get_input_states(transicion *transicion)
{
  if (transicion == NULL)
    return NULL;

  printf("%d\n", (transicion->input_states)[0]);
  return transicion->input_states;
}

int transicion_get_input_symbol(transicion *transicion)
{
  if (transicion == NULL)
  {
    return -1;
  }

  return transicion->input_symbol;
}

int *transicion_get_output_states(transicion *transicion)
{
  if (transicion == NULL)
    return NULL;

  return transicion->output_states;
}

char *transicion_get_input_state_name(AFND *AFND, transicion *transicion)
{
  char *nombre;
  char *nombre_aux;
  int i = 0;
  int len_aux;
  char* nombre_pointer;

  if (transicion == NULL || AFND == NULL || transicion->input_states == NULL)
  {
    return NULL;
  }

  nombre_aux = AFNDNombreEstadoEn(AFND, transicion->input_states[i]);
  len_aux = strlen(nombre_aux);

  /*nombre tiene el nombre del primer estado*/
  nombre = (char *)calloc(len_aux, sizeof(char *));
  strcpy(nombre, nombre_aux);

  /*Vamos añadiendo los nombre de los otro estados*/
  for (i = 1; transicion->input_states[i] != -1; i++)
  {
    /*Cogemos el nombre que corresponde*/
    nombre_aux = AFNDNombreEstadoEn(AFND, transicion->input_states[i]);

    /*Si el nombre no lo hemos añadido ya*/
    if (strstr(nombre, nombre_aux) == NULL)
    {
      /*Redimensionamos*/
      len_aux += strlen(nombre_aux);
      nombre_pointer = realloc(nombre, len_aux * sizeof(char *));
      nombre = nombre_pointer;

      /*añadimos la cadena*/
      strcat(nombre, nombre_aux);
    }
  }

  return nombre;
}

char *transicion_get_output_state_name(AFND *AFND, transicion *transicion)
{
  char *nombre;
  char *nombre_aux;
  int i = 0;
  int len_aux;

  if (transicion == NULL || AFND == NULL || transicion->output_states == NULL)
  {
    return NULL;
  }

  nombre_aux = AFNDNombreEstadoEn(AFND, transicion->output_states[i]);
  len_aux = strlen(nombre_aux);

  /*nombre tiene el nombre del primer estado*/
  nombre = (char *)calloc(len_aux, sizeof(char *));
  strcpy(nombre, nombre_aux);

  /*Vamos añadiendo los nombre de los otro estados*/
  for (i = 1; transicion->output_states[i] != -1; i++)
  {
    /*Cogemos el nombre que corresponde*/
    nombre_aux = AFNDNombreEstadoEn(AFND, transicion->output_states[i]);

    /*Si el nombre no lo hemos añadido ya*/
    
      /*Redimensionamos*/
      /*añadimos la cadena*/
      strcat(nombre, nombre_aux);
    
  }

  return nombre;
}

int transicion_get_output_state_type(AFND *AFND, transicion *transicion)
{
  int i, tipo;

  tipo = NORMAL;

  if (transicion == NULL || AFND == NULL || transicion->output_states == NULL)
  {
    return -1;
  }

  /*Bucle con el que miramos los estados de todos los estados*/
  /*Si un estado no es normal su tipo se "añade" al estado que estamos analizando*/
  for (i = 0; transicion->output_states[i] != -1; i++)
  {
    if (AFNDTipoEstadoEn(AFND, transicion->output_states[i]) == FINAL)
    {
      if (tipo == INICIAL)
      {
        tipo = INICIAL_Y_FINAL;
        return tipo;
      }
      tipo = FINAL;
    }
    else if (AFNDTipoEstadoEn(AFND, transicion->output_states[i] == INICIAL))
    {
      if (tipo == FINAL)
      {
        tipo = INICIAL_Y_FINAL;
        return tipo;
      }
      tipo = INICIAL;
    }
    else if (AFNDTipoEstadoEn(AFND, transicion->output_states[i]) == INICIAL_Y_FINAL)
    {
      tipo = INICIAL_Y_FINAL;
      return tipo;
    }
  }

  return tipo;
}

int transicion_get_input_state_type(AFND *AFND, transicion *transicion)
{
  int i, tipo;

  if (transicion == NULL || AFND == NULL || transicion->input_states == NULL)
  {
    return -1;
  }

  tipo = NORMAL;

  /*Bucle con el que miramos los estados de todos los estados*/
  /*Si un estado no es normal su tipo se "añade" al estado que estamos analizando*/
  for (i = 0; transicion->input_states[i] != -1; i++)
  {
    if (AFNDTipoEstadoEn(AFND, transicion->input_states[i]) == FINAL)
    {
      if (tipo == INICIAL)
      {
        tipo = INICIAL_Y_FINAL;
        return tipo;
      }
      tipo = FINAL;
    }
    else if (AFNDTipoEstadoEn(AFND, transicion->input_states[i] == INICIAL))
    {
      if (tipo == FINAL)
      {
        tipo = INICIAL_Y_FINAL;
        return tipo;
      }
      tipo = INICIAL;
    }
    else if (AFNDTipoEstadoEn(AFND, transicion->input_states[i]) == INICIAL_Y_FINAL)
    {
      tipo = INICIAL_Y_FINAL;
      return tipo;
    }
  }

  return tipo;
}

void transicion_debug(AFND *AFND, transicion *transicion)
{
  int i;

  if (transicion == NULL)
  {
    return;
  }
  printf("ESTADOS INICIALES: \n");
  for (i = 0; transicion->input_states[i] != -1; i++)
  {
    printf("\t%s \n", AFNDNombreEstadoEn(AFND, transicion->input_states[i]));
  }
  printf("\nSIMBOLO: \n");
  printf("\t%s\n", AFNDSimboloEn(AFND, transicion->input_symbol));

  printf("ESTADOS FINALES: \n");
  for (i = 0; transicion->output_states[i] != -1; i++)
  {
    printf("\t%s \n", AFNDNombreEstadoEn(AFND, transicion->output_states[i]));
  }
  printf("\n\n\n");
}
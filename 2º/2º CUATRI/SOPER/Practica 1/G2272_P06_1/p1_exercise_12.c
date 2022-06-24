/*
@fichero: p1_exercise_12.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 20/02/2019
@descripción: programa que mediante el uso de hilos, calculará
el exponencial en base 2 de un número definido en la estructura.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define N 5


typedef struct{
  int datos;   /*elementos de la estructura*/
  int sol;     /*resultado donde se guardará la operación*/
} resultados;

/*
@nombre: exponencial
@descripcion: calcula el exponencial en base 2
de un número.
@input: void* 
@output: void*, exponencial del número en base 2
*/

void *exponencial (void *arg) {
  int i, answ=1;
  resultados *prueba = (resultados *)arg;
  printf ("Dato del array: %d\n", prueba->datos);

  for ( i = 0 ; i < prueba->datos ; i++ )
    answ*=2;

  prueba->sol = answ;

  pthread_exit(NULL);
}

int main(int argc , char *argv[]) {
  int i;
  pthread_t *hilo = (pthread_t *)malloc(N*sizeof(pthread_t));
  if (hilo == NULL){
   printf ("Error reservando memoria hilos\n");
   exit(EXIT_FAILURE);
  }

  /*Creamos estructura donde almacenaremos los numeros X y los resultados*/
  resultados *res = (resultados *)malloc(N*sizeof(resultados));
  if (res == NULL){
    printf ("Error reservando memoria estructura resultados\n");
    free (hilo);
    exit(EXIT_FAILURE);
  }

  /*LLenamos los datos de nuestra estructura*/
  for (i = 0; i < N; i++)
    res[i].datos=i;

  for (i = 0; i < N; i++){
    pthread_create(&hilo[i], NULL , exponencial, (void *)&res[i]);
  }

  /*Se espera a que todos los hilos calculen sus exponenciales*/
  for (i = 0; i < N; i++)
    pthread_join(hilo[i], NULL);

  /*Imprimimos por pantalla todos los datos*/
  for (i = 0; i < N; i++)
    printf("Resultado de la potencia de base 2 y exponente %d es %d\n",res[i].datos, res[i].sol);

  free (hilo);
  free (res);
  printf("El programa %s termino correctamente \n", argv[0]);
  exit(EXIT_SUCCESS);
}

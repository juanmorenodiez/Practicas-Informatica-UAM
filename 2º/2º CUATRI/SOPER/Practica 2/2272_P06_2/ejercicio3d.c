/*
@fichero: ejercicio3d.c
@autores: Andrés Mena Godino y Juan Moreno Díez
@correos: andres.mena@estudiante.uam.es y juan.morenod@estudiante.uam.es
@grupo: 2272
@fecha: 05/03/2019
@descripción: programa que trata de capturar la señal
SIGKILL utilizando una función manejadora.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


/* manejador: rutina de tratamiento de la señal SIGKILL. */
void manejador(int sig) {
    printf("He conseguido capturar SIGKILL \n");
    fflush(stdout);
}

int main(void) {
    struct sigaction act;

    act.sa_handler = manejador;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;

    if (sigaction(SIGKILL, &act, NULL) < 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    while(1);
  }

/* Añadiendo el flag SA_RESETHAND (act.sa_flags = SA_RESETHAND;) se resetea el
manejador tras la primera invocación. */

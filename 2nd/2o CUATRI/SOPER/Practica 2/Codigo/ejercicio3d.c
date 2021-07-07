#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

/* manejador: rutina de tratamiento de la señal SIGINT. */
void manejador(int sig) {
    printf("He conseguido capturar %d\n", sig);
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

    while(1) {
        printf("En espera de Ctrl+C (PID = %d)\n", getpid());
        sleep(9999);
    }
}

/* Añadiendo el flag SA_RESETHAND (act.sa_flags = SA_RESETHAND;) se resetea el
manejador tras la primera invocación. */
/* Se puede utilizar este mismo código para el ejercicio 3. */

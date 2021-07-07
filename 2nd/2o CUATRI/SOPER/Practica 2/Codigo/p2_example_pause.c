#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* manejador_SIGTERM: saca un mensaje por pantalla y termina el proceso. */
void manejador_SIGTERM(int sig) {
    printf("Terminación del proceso %d a petición del usuario \n", getpid());
    fflush(stdout);
    exit(EXIT_SUCCESS);
}

/* manejador_SIGUSR1: presenta un número aleatorio por pantalla. */
void manejador_SIGUSR1(int sig) {
    printf("%d\n", rand());
    fflush(stdout);
}

int main(void) {
    struct sigaction act;

    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;

    /* Se arma la señal SIGTERM. */
    act.sa_handler = manejador_SIGTERM;
    if (sigaction(SIGTERM, &act, NULL) < 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    /* Se arma la señal SIGUSR1. */
    act.sa_handler = manejador_SIGUSR1;
    if (sigaction(SIGUSR1, &act, NULL) < 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    /* Se muestra el PID para facilitar el uso de kill.
    También se podría usar killall. */
    printf("PID: %d. Se esperan las señales SIGUSR1 o SIGTERM\n", getpid());

    while(1)
        pause(); /* Bloquea el proceso hasta que llegue una señal. */
}

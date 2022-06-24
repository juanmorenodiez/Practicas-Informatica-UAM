#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define SECS 10

/* manejador_SIGALRM: saca un mensaje por pantalla y termina el proceso. */
void manejador_SIGALRM(int sig) {
    printf("\nEstos son los numeros que me ha dado tiempo a contar\n");
    exit(EXIT_SUCCESS);
}

int main(void) {
    struct sigaction act;
    long int i;

    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;

    /* Se arma la señal SIGALRM. */
    act.sa_handler = manejador_SIGALRM;
    if (sigaction(SIGALRM, &act, NULL) < 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    if (alarm(SECS))
        fprintf(stderr, "Existe una alarma previa establecida\n");

    for (i=0;;i++) {
        fprintf(stdout, "%10ld\r", i);
        fflush(stdout);
    }

    fprintf(stdout, "Fin del programa\n");
    exit(EXIT_SUCCESS);
}

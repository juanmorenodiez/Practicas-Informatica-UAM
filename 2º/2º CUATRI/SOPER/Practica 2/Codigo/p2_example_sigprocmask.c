#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    sigset_t set, oset;

    /* Máscara que bloqueará la señal por error en coma flotante y por
    violación de segmento. */
    sigemptyset(&set);
    sigaddset(&set, SIGFPE);
    sigaddset(&set, SIGSEGV);

    /*Bloqueo de las señales SIGFPE y SIGSEV en el proceso. */
    if (sigprocmask(SIG_BLOCK, &set, &oset) < 0) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("En espera de señales (PID = %d)\n", getpid());
        printf("SIGFPE y SIGSEGV están bloqueadas\n");
        pause();
    }
}

/*
 * Programa principal del servidor.
 *
 * modulo: server.c
 * Pareja 10:
 *    Juan Moreno <juan.morenod@estudiante.uam.es>
 *    Ines Martin <ines.martinmateos@estudiante.uam.es>
 */

#include "libSockets.h"
#include "pool_thread.h"
#include <signal.h>

/*
 * Manejador vacio para cuando reciba SIGINT
 */
void empty_handler() {
    printf("Saliendo por CTRL+C\n");
    fflush(stdout);
    return;
}

int main() {
    struct sigaction act;
    sigset_t newmask, oldmask;
    pool_thread *pool;
    LibConfig *ficheroConfiguracion;

    ficheroConfiguracion = parseConfig();

    printf("CREANDO SOCKET\n");
    /*Creacion del socket.*/
    ficheroConfiguracion->sockval = createSocket();

    printf("BINDING SOCKET\n");
    /*Comprobamos si el socket ha sido creado para enviarlo.*/
    bindSocket(ficheroConfiguracion);

    printf("LISTEN SOCKET\n");
    /*Esperamos conexiones.*/
    listenSocket(ficheroConfiguracion);

    /*Aceptamos la conexion del cliente.*/
    printf("Esperando conexiones del cliente...\n");

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    if (pthread_sigmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        printf("Error en pthread_sigmask\n");
        exit(EXIT_FAILURE);
    }

    act.sa_mask = newmask;
    act.sa_flags = 0;

    act.sa_sigaction = empty_handler;
    if (sigaction(SIGINT, &act, NULL) < 0) {
        printf("Error en sigaction");
        return -1;
    }

	pool = pool_th_ini(ficheroConfiguracion);

    sigsuspend(&oldmask);

    /*Liberamos recursos*/
    pool_th_destroy(pool);
    close(ficheroConfiguracion->sockval);
    free(ficheroConfiguracion->server_root);
    free(ficheroConfiguracion->server_signature);
    free(ficheroConfiguracion->version);
    free(ficheroConfiguracion);

    exit(EXIT_SUCCESS);
}

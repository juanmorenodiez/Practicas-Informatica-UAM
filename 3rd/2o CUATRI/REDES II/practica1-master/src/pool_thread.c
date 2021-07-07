/*
 * Funciones basicas para la implementacion de un pool de hilos.
 *
 * modulo: pool_thread.c
 * Pareja 10:
 *    Juan Moreno <juan.morenod@estudiante.uam.es>
 *    Ines Martin <ines.martinmateos@estudiante.uam.es>
 */

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <strings.h>
#include "pool_thread.h"
#include "http.h"

/*
 * Estructura de datos del pool de hilos.
 */
struct pool_thread {
    int num_threads;
    pthread_t *threads;
};

/********
* FUNCION: pool_thread *pool_th_ini(LibConfig *configuration)
* ARGS_IN: LibConfig* configuration - informacion de configuracion del servidor
* DESCRIPCION: Funcion que crea el pool de hilos y asigna trabajo a cada hilo
* ARGS_OUT: pool_thread * - estructura de tipo pool_thread con el pool de hilos
********/
pool_thread *pool_th_ini(LibConfig *configuration) {
    pool_thread *pool = NULL;
    int i = 0;

    openlog("pool_th_ini", LOG_PID, LOG_USER);

    if(init_semaphores() == -1){
        syslog(LOG_ERR, "Error abriendo semáforos.");
        closelog();
    }

    pool = (pool_thread*) malloc(sizeof(pool_thread));
    if (pool == NULL) {
        syslog(LOG_ERR, "Error reservando memoria para el pool.\n");
        closelog();
        return NULL;
    }

    pool->threads = (pthread_t *) malloc(sizeof(pthread_t)*configuration->max_clients);
    pool->num_threads = configuration->max_clients;

    for (i = 0; i < pool->num_threads; i++) {
        if (pthread_create(&(pool->threads[i]), NULL, work_function, (void*)configuration) != 0) {
            syslog(LOG_ERR, "Error en pool_th_ini\n");
            closelog();
            pool_th_destroy(pool);
            return NULL;
        }
    }

    closelog();
    return pool;
}

/********
* FUNCION: int pool_th_destroy(pool_thread *pool)
* ARGS_IN: pool_thread* pool - variable de tipo pool_thread con el pool a liberar
* DESCRIPCION: Funcion que liberara los recursos creados de un pool de hilos
* ARGS_OUT: int - número entero (-1 si no se ha podido liberar toda la memoria, si todo correcto)
********/
int pool_th_destroy(pool_thread *pool) {
    int i = 0;
    if (pool == NULL) return -1;

    openlog("pool_th_destroy", LOG_PID, LOG_USER);

    for (i = 0; i < pool->num_threads; i++) {
        if (pthread_cancel(pool->threads[i]) != 0) {
            syslog(LOG_ERR, "Error in pthread_cancel.\n");
            closelog();
            return -1;
        }

        if (pthread_join(pool->threads[i], NULL) != 0) {
            syslog(LOG_ERR, "Error in pthread_join.\n");
            closelog();
            return -1;
        }
    }

    free(pool->threads);
    free(pool);
    close_semaphores();
    closelog();
    return 0;
}

/********
* FUNCION: void *work_function(void* configuration)
* ARGS_IN: void *configuration - informacion de configuracion del servidor
* DESCRIPCION: Funcion de trabajo de cada hilo
* ARGS_OUT: void *
********/
void *work_function(void *configuration) {

    while (1) {
        manejador((LibConfig*) configuration);
    }

    return NULL;
}

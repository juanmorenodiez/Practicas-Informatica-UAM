/*
 * Librería para el manejo de hilos en C.
 *
 * modulo: pool_thread.h
 * Pareja 10:
 *    Juan Moreno <juan.morenod@estudiante.uam.es>
 *    Ines Martin <ines.martinmateos@estudiante.uam.es>
 */

#ifndef _POOL_THREAD_H
#define _POOL_THREAD_H

#include "libSockets.h"
#include "http.h"
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <syslog.h>

typedef struct pool_thread pool_thread;

pool_thread *pool_th_ini(LibConfig *configuration);
int pool_th_destroy(pool_thread *pool);
void *work_function(void *configuration);

#endif

/*
 * Librería para funciones del servidor que atiende a peticiones HTTP.
 *
 * modulo: http.h
 * Pareja 10:
 *    Juan Moreno <juan.morenod@estudiante.uam.es>
 *    Ines Martin <ines.martinmateos@estudiante.uam.es>
 */

 #ifndef _HTTP_H
 #define _HTTP_H

#include "libSockets.h"
#include "picohttpparser.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <syslog.h>
#include <dirent.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <strings.h>
#include <sys/wait.h>

#define SEM_ACCEPT "/accept_sem"
#define SEM_SEND "/send_sem"
#define READ 0
#define WRITE 1

int run_script(char *command, char *argFile, char *args);
int get_content_type(char *recurso, char *extension, char *contentType);
void get_arguments(char *metodo, char *message, int pret, char *recurso, char *valor);
void get_dates(char *date, char *fileName, char *last_modified);
int send_file(char *fileName, char *contenido, int client);
int get_file_length(char *fileName, char *status_code, char *contentType, LibConfig *configuration);
void ejecutar_scripts(char *fileName, char *metodo, char *valor, char *extension, LibConfig *configuration);
int init_semaphores();
void close_semaphores();
void manejador(LibConfig *configuration);

#endif

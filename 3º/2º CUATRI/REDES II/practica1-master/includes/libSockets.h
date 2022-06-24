/*
 * Librería para el uso de sockets en C.
 *
 * modulo: libSockets.h
 * Pareja 10:
 *    Juan Moreno <juan.morenod@estudiante.uam.es>
 *    Ines Martin <ines.martinmateos@estudiante.uam.es>
 */

#ifndef _LIB_SOCKETS_H
#define _LIB_SOCKETS_H

#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <confuse.h>

#define TAM_MESSAGE 1024
#define EMPTY 0
#define TAM_STRING 50

typedef struct _LibConfig {
    char * server_root;
    long int max_clients;
    long int listen_port;
    char * server_signature;
    char * version;
    int sockval;
} LibConfig;

int createSocket();
void bindSocket(LibConfig *configuration);
void listenSocket(LibConfig *configuration);
int accept_connection(int sockval);

LibConfig *parseConfig();

#endif

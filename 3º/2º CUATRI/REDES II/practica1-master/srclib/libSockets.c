/*
 * Libreria con los metodos para la creacion y uso de sockets.
 *
 * modulo: libSockets.c
 * Pareja 10:
 *    Juan Moreno <juan.morenod@estudiante.uam.es>
 *    Ines Martin <ines.martinmateos@estudiante.uam.es>
 */

#include "libSockets.h"

/*******************************
****METODOS PARA LOS SOCKETS****
********************************/

/********
* FUNCION: int createSocket()
* ARGS_IN:
* DESCRIPCION: Funcion que crea el socket
* ARGS_OUT: int - valor del socket
********/
int createSocket(){
    int sockval;

    syslog (LOG_INFO, "Creating socket");
    if ( (sockval = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        syslog(LOG_ERR, "Error creating socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(sockval, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0){
        perror("setsockopt(SO_REUSEADDR) failed");
    }

    return sockval;
}

/********
* FUNCION: void bindSocket(LibConfig * configuration)
* ARGS_IN: LibConfig* configuration - informacion de configuracion del servidor
* DESCRIPCION: Funcion que realiza el bind del socket al puerto correspondiente
* ARGS_OUT: void
********/
void bindSocket(LibConfig * configuration){
    struct sockaddr_in Direccion;

    bzero((void *)&(Direccion.sin_zero), 8);
    Direccion.sin_family=AF_INET; /* TCP/IP family */
    Direccion.sin_port=htons(configuration->listen_port); /* Asigning port */
    Direccion.sin_addr.s_addr=htonl(INADDR_ANY); /* Accept all adresses */

    syslog (LOG_INFO, "Binding socket");
    if (bind (configuration->sockval, (struct sockaddr *)&Direccion, sizeof(Direccion))<0){
        syslog(LOG_ERR, "Error binding socket");
        close(configuration->sockval);
        exit(EXIT_FAILURE);
    }

    return ;
}

/********
* FUNCION: void listenSocket(LibConfig * configuration)
* ARGS_IN: LibConfig* configuration - informacion de configuracion del servidor
* DESCRIPCION: Funcion que prepara el socket para recibir conexiones
* ARGS_OUT: void
********/
void listenSocket(LibConfig * configuration){
    syslog (LOG_INFO, "Listening connections");
    if (listen (configuration->sockval, configuration->max_clients)<0){
        syslog(LOG_ERR, "Error listenining");
        close(configuration->sockval);
        exit(EXIT_FAILURE);
    }

    return ;
}

/********
* FUNCION: int accept_connection(int sockval)
* ARGS_IN: int sockval - valor del socket
* DESCRIPCION: Funcion que acepta una conexion del cliente
* ARGS_OUT: int - valor del cliente
********/
int accept_connection(int sockval){
    int client;
    socklen_t len;
    struct sockaddr Conexion;

    len = sizeof(Conexion);

    if ((client = accept(sockval, &Conexion, &len)) < 0){
        syslog(LOG_ERR, "Error accepting connection");
        close(sockval);
        exit(EXIT_FAILURE);
    }

    return client;
}


/***********************************************
****METODOS PARA EL FICHERO DE CONFIGURACION****
************************************************/

/********
* FUNCION: LibConfig * parseConfig()
* ARGS_IN:
* DESCRIPCION: Funcion que parsea el fichero de configuracion
* ARGS_OUT: LibConfig * - informacion de configuracion del servidor
********/
LibConfig * parseConfig(){
    LibConfig * config = NULL;

    config = (LibConfig*) malloc(sizeof(LibConfig));
    if(config == NULL) return NULL;

    config->server_root = NULL;
    config->max_clients = 0;
    config->listen_port = 0;
    config->server_signature = NULL;
    config->version = NULL;

    cfg_opt_t opts[] = {
       CFG_SIMPLE_STR("server_root", &config->server_root),
       CFG_SIMPLE_INT("max_clients", &config->max_clients),
       CFG_SIMPLE_INT("listen_port", &config->listen_port),
       CFG_SIMPLE_STR("server_signature", &config->server_signature),
       CFG_SIMPLE_STR("version", &config->version),
       CFG_END()
   };

   cfg_t *cfg;
   cfg = cfg_init(opts, 0);

   cfg_parse(cfg, "server.conf");

   cfg_free(cfg);

   return config;
}

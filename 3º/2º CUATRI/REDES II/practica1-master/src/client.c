/*
 * modulo: client.c
 * Pareja 10:
 *    Juan Moreno <juan.morenod@estudiante.uam.es>
 *    Ines Martin <ines.martinmateos@estudiante.uam.es>
 */

#include "libSockets.h"

int main(int argc, char **argv){
    int valueSocket;
    struct sockaddr_in Direccion;
    valueSocket = createSocket();
    char * message = strcat(argv[1], "\n");

    Direccion.sin_family = AF_INET;
    Direccion.sin_addr.s_addr = inet_addr("127.0.0.1");
    Direccion.sin_port = htons(8080);

    if (connect (valueSocket, (struct sockaddr *)&Direccion, sizeof (Direccion)) == -1){
        syslog(LOG_ERR, "Error de la conexion del cliente\n");
        close(valueSocket);
        exit(EXIT_FAILURE);
    }

    // Envia mensaje al servidor (send())
    if (send (valueSocket, message, strlen(message), EMPTY) == -1){
        syslog(LOG_ERR, "Error al enviar un paquete al servidor\n");
        close(valueSocket);
        exit(EXIT_FAILURE);
    }
    close(valueSocket);
}

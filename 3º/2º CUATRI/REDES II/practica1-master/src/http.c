/*
 * Modulo para funciones del servidor que atiende a peticiones HTTP.
 *
 * modulo: http.c
 * Pareja 10:
 *    Juan Moreno <juan.morenod@estudiante.uam.es>
 *    Ines Martin <ines.martinmateos@estudiante.uam.es>
 */

#include "http.h"

/*
 * Semaforos para controlar el acceso de los hilos.
 */
sem_t *accept_sem = NULL, *send_sem = NULL;


/********
* FUNCION: int init_semaphores()
* ARGS_IN:
* DESCRIPCION: Funcion que inicializa los semáforos
* ARGS_OUT: int - 0 si se ha ejecutado correctamente, en caso contrario -1
********/
int init_semaphores(){
    sem_unlink(SEM_ACCEPT);
    if ((accept_sem = sem_open(SEM_ACCEPT, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
        return -1;
    }

    sem_unlink(SEM_SEND);
    if ((send_sem = sem_open(SEM_SEND, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
        return -1;
    }

    return 0;
}

/********
* FUNCION: void close_semaphores()
* ARGS_IN:
* DESCRIPCION: Funcion que cierra los semáforos
* ARGS_OUT:
********/
void close_semaphores(){
    sem_unlink(SEM_ACCEPT);
    sem_close(accept_sem);
    sem_unlink(SEM_SEND);
    sem_close(send_sem);
}

/********
* FUNCION: int run_script(char *command, char *argFile, char *args)
* ARGS_IN: char *command - comando para ejecutar los scripts
*          char *argFile - fichero/script
*          char *args - argumentos GET o POST
* DESCRIPCION: Funcion que ejecuta un script mediante pipes.
* ARGS_OUT: int - pipe de lectura para recuperar la salida.
********/
int run_script(char *command, char *argFile, char *args){
    pid_t pid;
    int child_in[2];
    int child_out[2];
    pipe(child_in);
    pipe(child_out);
    pid = fork();

    if (pid != 0) {
        close(child_in[READ]);
        close(child_out[WRITE]);

        if (stdin)
            write(child_in[WRITE], stdin, strlen((char*)stdin));

        close(child_in[WRITE]);
        wait(NULL);

        return child_out[READ];
    }

    close(child_out[READ]);
    close(child_in[WRITE]);
    dup2(child_in[READ], STDIN_FILENO);
    dup2(child_out[WRITE], STDOUT_FILENO);

    // execlp para ejecutar el comando con los argumentos
    return execlp(command, command, argFile, args, (char *) NULL);
}

/********
* FUNCION: int get_content_type(char *recurso, char *extension, char *contentType)
* ARGS_IN: char *recurso - recurso solicitado en la petición http
*          char *extension - extensión del recurso solicitado
*          char *contentType - valor del content-type que se incluirá en la cabecera de la respuesta
* DESCRIPCION: Funcion que obtiene el valor del content-type de la respuesta Http
* ARGS_OUT: int - tipoPOST flag que se utilizará para diferenciar los scripts del resto de recursos
********/
int get_content_type(char *recurso, char *extension, char *contentType){
    int tipoPOST = 0;

    if(strcmp(recurso, "/") == 0){
        strcpy(recurso, "/index.html");
    }

    // Se obtiene la extensión del recurso mediante strtok
    strtok(recurso, ".");
    strcpy(extension, strtok(NULL, "."));

    // En función de la extensión se elige un content type
    if(strcmp(extension,"html") == 0 || strcmp(extension, "htm") == 0) {
        strcpy(contentType, "text/html");
    }else if(strcmp(extension,"txt") == 0) {
        strcpy(contentType, "text/plain");
    }else if(strcmp(extension,"gif") == 0) {
        strcpy(contentType, "image/gif");
    }else if(strcmp(extension,"ico") == 0) {
        strcpy(contentType, "image/x-icon");
    }else if(strcmp(extension,"jpeg") == 0 || strcmp(extension,"jpg") == 0) {
        strcpy(contentType, "image/jpeg");
    }else if(strcmp(extension,"mpeg") == 0 || strcmp(extension,"mpg") == 0) {
        strcpy(contentType, "video/mpeg");
    }else if(strcmp(extension,"doc") == 0 || strcmp(extension,"docx") == 0) {
        strcpy(contentType, "application/msword");
    }else if(strcmp(extension,"pdf") == 0) {
        strcpy(contentType, "application/pdf");
    }else if(strcmp(extension,"php") == 0 || strcmp(extension,"py") == 0) {
        strcpy(contentType, "text/plain");
        tipoPOST = 1;
    }else{
        tipoPOST = -1;
    }

    return tipoPOST;
}

/********
* FUNCION: void get_arguments(char *metodo, char *message, int pret, char *recurso, char *valor)
* ARGS_IN: char *metodo - Método de la petición http
*          char *message - petición http
*          int pret - valor de retorno del método de parseo
*          char *recurso - recurso solicitado
*          char *valor - variable en la que se guardarán los argumentos
* DESCRIPCION: Funcion que obtiene los argumentos para las peticiones de tipo GET y/o POST
* ARGS_OUT:
********/
void get_arguments(char *metodo, char *message, int pret, char *recurso, char *valor){
    char valorPOST[TAM_STRING] = "", valorGET[TAM_STRING] = "",
        argumento[TAM_STRING] = "", argumentoPOST[TAM_STRING] = "";

    // Parseamos argumentos en el recurso (GET) a partir del símbolo '?'
    strtok(recurso, "?");
    char* token = strtok(NULL, "?");
    if(token != NULL){
        // Unicamente nos interesa el valor, que estará a la derecha del '=' (argumentoGET=hola+mundo+GET)
        strcpy(argumento, token);
        strtok(argumento, "=");
        token = strtok(NULL, "=");

        if(token != NULL)
            strcpy(valor, token);
    }

    // Para argumentos del post, parseamos desde el body de la peticion (message + pret)
    if(strcmp(metodo, "POST") == 0){
        sprintf(argumentoPOST, "%s", message + pret);
        if(argumentoPOST != NULL){
            strtok(argumentoPOST, "=");
            if(strlen(valor) == 0){
                token = strtok(NULL, "=");
                if(token != NULL)
                    strcpy(valor, token);
            }else{
                // Concatenamos argumentos si se ha ejecutado GET+POST
                token = strtok(NULL, "=");
                if(token != NULL){
                    strcpy(valorPOST, token);
                    strcpy(valorGET, valor);
                    sprintf(valor, "%s %s", valorGET, valorPOST);
                }
            }
        }
    }
}

/********
* FUNCION: void get_dates(char *date, char *fileName, char *last_modified)
* ARGS_IN: char *date - fecha actual
*          char *fileName - nombre del fichero
*          char *last_modified - fecha de última modificacion del fichero
* DESCRIPCION: Funcion que obtiene los campos de fechas para la cabecera
* ARGS_OUT:
********/
void get_dates(char *date, char *fileName, char *last_modified){
    time_t now = time(0);
    struct stat stt = {0};
    struct tm tm = *gmtime(&now);
    int var = 0;

    // Fecha actual
    strftime(date, sizeof date, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    var = strcmp(fileName, "");
    if(var != 0){
        // Ultima fecha de modificacion de fileName
        stat(fileName, &stt);
        struct tm lm = *gmtime(&(stt.st_mtime));
        strftime(last_modified, sizeof last_modified, "%a, %d %b %Y %H:%M:%S %Z", &lm);
    }
}

/********
* FUNCION: int send_file(char *fileName, char *contenido, int client)
* ARGS_IN: char *fileName - nombre del fichero
*          char *contenido - contenido del fichero
*          int client - cliente a enviar el fichero
* DESCRIPCION: Funcion envía un fichero solicitado al cliente
* ARGS_OUT: int - 0 si se ha ejecutado correctamente, en caso contrario -1
********/
int send_file(char *fileName, char *contenido, int client){
    int descriptor = open(fileName, O_RDONLY); //abre un descriptor de fichero
    long longitud = 0;

    if(descriptor < 0) {
        syslog(LOG_ERR, "Error while opening descriptor. %s not exists", fileName);
        return -1;
    }

    // Mientras siga habiendo informacion, se envia por bloques de tamaño TAM_MESSAGE
    do {
        longitud = read(descriptor, contenido, TAM_MESSAGE);
        if(longitud < 0) {
            syslog(LOG_ERR, "Error length.");
            close(descriptor);
            return -1;
        }else if(longitud > 0){
            if(send(client, contenido, longitud, MSG_NOSIGNAL) == -1){
                syslog(LOG_ERR, "Error while sending value.");
                close(descriptor);
                return -1;
            }
        }
    } while(longitud == TAM_MESSAGE);

    close(descriptor);

    return 0;
}

/********
* FUNCION: int get_file_length(char *fileName, char *status_code, char *contentType, LibConfig *configuration)
* ARGS_IN: char *fileName - nombre del fichero
*          char *status_code - código de respuesta de la petición
*          char *contentType - content-type de la respuesta del servidor
*          LibConfig *configuration - informacion de configuracion del servidor
* DESCRIPCION: Funcion que obtiene la longitud del fichero que se va a enviar
* ARGS_OUT: int - longitud del fichero
********/
int get_file_length(char *fileName, char *status_code, char *contentType, LibConfig *configuration){
    FILE *file = fopen(fileName, "rb+");
    long longitud = 0;

    if(file == NULL) {
        // Si el fichero no existe, preparamos el 404 Not Found para ser enviado
        syslog(LOG_ERR, "Error 404 Not Found");
        strcpy(status_code, "404 Not Found");
        sprintf(fileName, "%s/error404.html", configuration->server_root);
        strcpy(contentType, "text/html");
        file = fopen(fileName, "rb+");
    }

    // Apuntamos al final del fichero para obtener la longitud con ftell
    fseek(file, 0, SEEK_END);
    longitud = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);

    return longitud;
}

/********
* FUNCION: void ejecutar_scripts(char *fileName, char *metodo, char *valor, char *extension, LibConfig *configuration)
* ARGS_IN: char *fileName - nombre del fichero
*          char *metodo - método enviado en la petición
*          char *valor - valor de los argumentos de la petición
*          char *extension - extensión del script
*          LibConfig* configuration - informacion de configuracion del servidor
* DESCRIPCION: Funcion que lanza el script en función de su extensión, y escribe el resultado en un fichero
* ARGS_OUT:
********/
void ejecutar_scripts(char *fileName, char *metodo, char *valor, char *extension, LibConfig *configuration){
    char readbuf[1024] = "";
    int ret = 0;

    syslog(LOG_INFO, "Ejecutando script %s con metodo %s...", fileName, metodo);

    if(strcmp(extension, "py") == 0){
        ret = run_script("python3", fileName, valor);
    }else{
        ret = run_script("php", fileName, valor);
    }

    sprintf(fileName, "%s/return.txt", configuration->server_root);

    // Escribimos resultado en el fichero htmlfiles/return.txt
    FILE * fp = fopen(fileName, "w+");
    while(read(ret, readbuf, sizeof(readbuf-1))){
        fprintf(fp, "%s", readbuf);
    }
    fclose(fp);
}

/********
* FUNCION: void manejador(LibConfig *configuration)
* ARGS_IN: LibConfig *configuration - informacion de configuracion del servidor
* DESCRIPCION: Funcion que maneja las peticiones del cliente y genera una respuesta (HTTP)
* ARGS_OUT: void
********/
void manejador(LibConfig *configuration) {
    char *message = NULL, *metodo = NULL, *fileName = NULL,
         *respuesta = NULL, *contentType = NULL, *contenido = NULL,
         *status_code = NULL, *comando = NULL;

    char date[TAM_MESSAGE] = "", last_modified[TAM_MESSAGE] = "",
        extension[TAM_STRING] = "", recurso[TAM_STRING] = "", valor[TAM_STRING*2] = "";

    const char *method = NULL, *path = NULL;
    struct phr_header headers[100];
    int receive = 0, client = 0, pret = 0, minor_version = 1, tipoPOST = 0;
    size_t buflen = 0, prevbuflen = 0, method_len = 0, path_len = 0, num_headers = 0;
    long longitud = 0;

    sem_wait(accept_sem);
    client = accept_connection(configuration->sockval);
    sem_post(accept_sem);

    openlog("IM_JM_P10", LOG_PID, LOG_USER); // Apertura para los syslog

    // Reserva de memoria
    message = (char*) malloc((TAM_MESSAGE)*sizeof(char));
    if(message == NULL) return;

    metodo = (char*) malloc((TAM_STRING)*sizeof(char));
    if(metodo == NULL) return;

    fileName = (char*) malloc((TAM_STRING)*sizeof(char));
    if(fileName == NULL) return;

    respuesta = (char*) malloc((TAM_MESSAGE)*sizeof(char));
    if(respuesta == NULL) return;

    contentType = (char*) malloc((TAM_STRING)*sizeof(char));
    if(contentType == NULL) return;

    contenido = (char*) malloc((TAM_MESSAGE)*sizeof(char));
    if(contenido == NULL) return;

    status_code = (char*) malloc((TAM_STRING)*sizeof(char));
    if(status_code == NULL) return;

    comando = (char*) malloc((TAM_STRING*2)*sizeof(char));
    if(comando == NULL) return;

    // pthread_cleanup_push para liberar correctamente memoria al cerrar la ejecucion
    pthread_cleanup_push(free, message);
    pthread_cleanup_push(free, metodo);
    pthread_cleanup_push(free, fileName);
    pthread_cleanup_push(free, respuesta);
    pthread_cleanup_push(free, contentType);
    pthread_cleanup_push(free, contenido);
    pthread_cleanup_push(free, status_code);
    pthread_cleanup_push(free, comando);

    // Recepcion de peticion
    receive = recv (client, message, TAM_MESSAGE, EMPTY);
    if (receive == -1) {
        syslog(LOG_ERR, "Error al recibir una peticion del cliente.");
    }else if (receive == 0) {
        syslog(LOG_NOTICE, "Peticion vacia.");
    }else {
        prevbuflen = buflen;
        buflen += receive;

        // Parseo de peticion
        num_headers = sizeof(headers) / sizeof(headers[0]);
        pret = phr_parse_request(message, buflen, &method, &method_len,
                                 &path, &path_len, &minor_version, headers,
                                 &num_headers, prevbuflen);

        // Comprobación de existencia de directorio raiz de recursos
        DIR *d = opendir(configuration->server_root);
        if(d == NULL){
            syslog(LOG_ERR, "El directorio raiz no existe.");
            break;
        }else{
            closedir(d);
        }

        if(pret <= 0) {
            syslog(LOG_ERR, "Error 400 Bad Request");
            strcpy(status_code, "400 Bad Request");
            sprintf(fileName, "%s/error400.html", configuration->server_root);
            strcpy(metodo, "GET");
            strcpy(contentType, "text/html");
        }else{
            sprintf(metodo, "%.*s", (int)method_len, method);
            sprintf(recurso, "%.*s", (int)path_len, path);

            // Obtencion de argumentos y content-type
            get_arguments(metodo, message, pret, recurso, valor);
            tipoPOST = get_content_type(recurso, extension, contentType);
        }

        syslog(LOG_INFO, "METODO: %s", metodo);
        if(strcmp(metodo, "GET") == 0 || strcmp(metodo,"POST") == 0) {
            syslog(LOG_INFO, "Servidor atendiendo peticion %s %s.%s", metodo, recurso, extension);
            if(pret > 0){
                // Preparacion del recurso y el status satisfactorio
                sprintf(fileName, "%s%s.%s", configuration->server_root, recurso, extension);
                strcpy(status_code, "200 OK");
            }

            if(strcmp(extension, "php") == 0 || strcmp(extension,"py") == 0){
                ejecutar_scripts(fileName, metodo, valor, extension, configuration);
            }

            // Obtencion de parametros de longitud del fichero y fechas
            longitud = get_file_length(fileName, status_code, contentType, configuration);
            get_dates(date, fileName, last_modified);

            // Preparacion y envio de cabeceras
            sprintf(respuesta,"HTTP/1.%d %s\r\nDate: %s\r\nServer: %s/%s\r\nLast-Modified: %s\r\nContent-Length: %ld\r\nContent-Type: %s\r\n\r\n", minor_version, status_code, date, configuration->server_signature, configuration->version, last_modified, longitud, contentType);
            send(client, respuesta, strlen(respuesta), EMPTY);

            // Envio de recurso
            sem_wait(send_sem);
            send_file(fileName, contenido, client);
            sem_post(send_sem);
        }else{

            if(tipoPOST == 0){
                sprintf(contenido, "La opcion disponible para los ficheros con extension %s es GET.\n", extension);
            }else if (tipoPOST == 1){
                sprintf(contenido, "La opcion disponible para los ficheros con extension %s es POST.\n", extension);
            }else{
                sprintf(contenido, "No existen opciones disponibles para este formato de fichero: %s\n", extension);
            }

            strcpy(fileName, "");
            get_dates(date, fileName, last_modified);

            // Envio de respuesta a peticiones OPTIONS
            sprintf(respuesta,"HTTP/1.%d 200 OK\r\nAllow: OPTIONS, GET, POST\r\nDate: %s\r\nServer: %s/%s\r\nContent-Length: %ld\r\nContent-Type: text/plain\r\n\r\n%s", minor_version, date, configuration->server_signature, configuration->version, strlen(contenido), contenido);
            send(client, respuesta, strlen(respuesta), EMPTY);
        }
    }

    // Pops para liberar memoria de las variables
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    close(client);
    closelog();
    return;
}

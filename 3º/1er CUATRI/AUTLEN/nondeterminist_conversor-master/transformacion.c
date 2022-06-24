#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conjunto.h"
#include "afnd.h"
#include "transicion.h"
#include "transformacion.h"

/*Funciones de manipulacion de arrays de enteros*/
int isInArrayEstados(int *arrayEstados, int number, int tamano);
int anadir_estados_array(int **estados_ini, int *estados_extra);
int *copiar_array(int *array_original);
int contar_array(int *array_original);
int is_content_equal(int *array_1, int *array_2);
int n_estados_insertados = 0;

AFND *AFND_convertir_a_determinista(AFND *original)
{
    transicion **tabla_transicion;
    int n_estados, n_simbolos, i, j, condicion_input, condicion_output;
    int tipo_input, tipo_output;
    char *nombre_input, *nombre_output, *nombre_simbolo;
    AFND *determinista;

    n_simbolos = AFNDNumSimbolos(original);

    tabla_transicion = AFND_obtener_tabla_transicion(original, &n_estados);

    determinista = AFNDNuevo("determinista", n_estados, n_simbolos);

    for (i = 0; i < n_simbolos; i++)
    {
        AFNDInsertaSimbolo(determinista, AFNDSimboloEn(original, i));
    }

    for (i = 0; tabla_transicion[i] != NULL; i++)
    {

        condicion_input = 0;
        condicion_output = 0;

        nombre_input = transicion_get_input_state_name(original, tabla_transicion[i]);
        nombre_output = transicion_get_output_state_name(original, tabla_transicion[i]);
        nombre_simbolo = AFNDSimboloEn(determinista, transicion_get_input_symbol(tabla_transicion[i]));
        tipo_input = transicion_get_input_state_type(original, tabla_transicion[i]);
        tipo_output = transicion_get_output_state_type(original, tabla_transicion[i]);
        /*añadimos los estados si no se encontraban antes*/
        for (j = 0; j < n_estados_insertados; j++)
        {
            if (strcmp(nombre_input, AFNDNombreEstadoEn(determinista, j)) == 0)
            {
                condicion_input = 1;
            }
            if (strcmp(nombre_output, AFNDNombreEstadoEn(determinista, j)) == 0)
            {
                condicion_output = 1;
            }
        }
        if (condicion_input == 0)
        {
            n_estados_insertados++;
            AFNDInsertaEstado(determinista, nombre_input, tipo_input);
        }
        if (condicion_output == 0)
        {
            n_estados_insertados++;
            AFNDInsertaEstado(determinista, nombre_output, tipo_output);
        }

        /*Solo queda añadir la transicion*/
        AFNDInsertaTransicion(determinista, nombre_input, nombre_simbolo, nombre_output);
        free(nombre_input);
        free(nombre_output);
    }

    /*Liberamos la tabla de transiciones*/
    /*Al primer estado no se transita*/
    free(transicion_get_input_states(tabla_transicion[0]));
    for (i = 0; tabla_transicion[i] != NULL; i++)
    {
        transicion_free(tabla_transicion[i]);
    }

    free(tabla_transicion);

    return determinista;
}

AFND *minimizar_determinista(AFND *original)
{
    AFND *determinista;
    AFND *minimo;
    int **matriz;
    int *estados_aux;
    int i, j, aux;
    int estados, simbolos;
    conjunto **subconjuntos;
    char *nombre_aux, *nombre_aux2;
    char *nombre, *nombre_simbolo;
    int len_aux;
    int tipo_aux;

    if (original == NULL)
    {
        return NULL;
    }

    determinista = AFND_convertir_a_determinista(original);
    
    estados = AFNDNumEstados(determinista);
    simbolos = AFNDNumSimbolos(determinista);

    /*Inicializamos los valores de la matriz con los FINALES/INICIAL_Y_FINAL y los otros tipos de estados*/
    matriz = (int **)calloc(estados, sizeof(int *));
    for (i = 0; i < estados; i++)
    {
        matriz[i] = (int *)calloc(estados, sizeof(int));
    }
    for (i = 0; i < estados; i++)
    {
        for (j = 0; j < estados; j++)
        {
            if ((AFNDTipoEstadoEn(determinista, i) == FINAL || AFNDTipoEstadoEn(determinista, i) == INICIAL_Y_FINAL) && (AFNDTipoEstadoEn(determinista, j) != FINAL && AFNDTipoEstadoEn(determinista, j) != INICIAL_Y_FINAL))
            {
                matriz[i][j] = 1;
            }
            else if ((AFNDTipoEstadoEn(determinista, j) == FINAL || AFNDTipoEstadoEn(determinista, j) == INICIAL_Y_FINAL) && (AFNDTipoEstadoEn(determinista, i) != FINAL && AFNDTipoEstadoEn(determinista, i) != INICIAL_Y_FINAL))
            {
                matriz[i][j] = 1;
            }
        }
    }

    /*Calculamos la matriz*/
    calcular_matriz(determinista, matriz);

    /*PRINTS FOR DEBUGGING*/
    /*
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < i; j++)
        {
            printf("|%d ", matriz[i][j]);
        }
        printf("\n");
    }
    */

    /*Obtenemos todos los subconjuntos posibles.*/
    subconjuntos = get_subconjuntos(matriz, estados);

    /*PRINTS FOR DEBUGGING*/
    /*
    for (i = 0; subconjuntos[i] != NULL; i++)
    {
        printf("ESTADOS EN EL SUBCONJUNTO %d: \n", i);
        estados_aux = conjunto_get_estados(subconjuntos[i]);
        aux = conjunto_get_cantidad(subconjuntos[i]);
        for (j = 0; j < aux; j++)
        {
            printf("%s\n", AFNDNombreEstadoEn(determinista, estados_aux[j]));
        }
        printf("\n\n");
    }
    */

    for (aux = 0; subconjuntos[aux] != NULL; aux++)
        ;

    /*Ahora ya podemos crear el minimo automata*/
    minimo = AFNDNuevo("minimo", aux, simbolos);

    /*anadimos los simbolos*/
    for (i = 0; i < simbolos; i++)
    {
        AFNDInsertaSimbolo(minimo, AFNDSimboloEn(determinista, i));
    }

    /*anadimos los nuevos estados*/
    for (i = 0; subconjuntos[i] != NULL; i++)
    {
        tipo_aux = NORMAL;
        estados_aux = conjunto_get_estados(subconjuntos[i]);
        aux = conjunto_get_cantidad(subconjuntos[i]);
        nombre_aux = AFNDNombreEstadoEn(determinista, estados_aux[0]);
        len_aux = strlen(nombre_aux);

        /*******************************************/
        /****************CALCULO NOMBRE*************/
        /*******************************************/
        /*nombre tiene el nombre del primer estado*/
        nombre = (char *)calloc(len_aux, sizeof(char *));
        strcpy(nombre, nombre_aux);

        /*Vamos añadiendo los nombre de los otro estados*/
        for (j = 1; j < aux; j++)
        {
            /*Cogemos el nombre que corresponde*/
            nombre_aux = AFNDNombreEstadoEn(determinista, estados_aux[j]);

            /*Redimensionamos*/
            len_aux += strlen(nombre_aux);
            nombre = realloc(nombre, len_aux * sizeof(char *));
            /*añadimos la cadena*/
            strcat(nombre, nombre_aux);
        }
        /*******************************************/
        /**************FIN CALCULO NOMBRE***********/
        /*******************************************/

        /*CALCULO DEL TIPO DEL ESTADO*/
        for (j = 0; j < aux; j++)
        {
            if (AFNDTipoEstadoEn(determinista, estados_aux[j]) == INICIAL)
            {
                if (tipo_aux == FINAL)
                {
                    tipo_aux = INICIAL_Y_FINAL;
                }
                else if (tipo_aux == NORMAL)
                {
                    tipo_aux = INICIAL;
                }
            }
            else if (AFNDTipoEstadoEn(determinista, estados_aux[j]) == FINAL)
            {
                if (tipo_aux == INICIAL)
                {
                    tipo_aux = INICIAL_Y_FINAL;
                }
                else if (tipo_aux == NORMAL)
                {
                    tipo_aux = FINAL;
                }
            }
        }
        /*anadimos el estado*/
        AFNDInsertaEstado(minimo, nombre, tipo_aux);
        free(nombre);
    }

    /*anadimos las transiciones*/
    for (i = 0; subconjuntos[i] != NULL; i++)
    {
        estados_aux = conjunto_get_estados(subconjuntos[i]);
        /*Como sabemos que los hemos introducido en order en minimo*/
        /*Podemos ir introduciendo las transiciones en orden*/
        nombre = AFNDNombreEstadoEn(minimo, i);
        for (j = 0; j < simbolos; j++)
        {
            nombre_simbolo = AFNDSimboloEn(determinista, j);
            /*Obtenemos el nombre del estado al que transita comprobando todos los estados*/
            for (aux = 0; AFNDTransicionIndicesEstadoiSimboloEstadof(determinista, estados_aux[0], j, aux) != 1; aux++)
                ;

            nombre_aux2 = AFNDNombreEstadoEn(determinista, aux);
            /*Ahora vemos con que nuevo estado corresponde*/
            for (aux = 0; strstr(AFNDNombreEstadoEn(minimo, aux), nombre_aux2) == NULL; aux++)
                ;

            nombre_aux = AFNDNombreEstadoEn(minimo, aux);

            AFNDInsertaTransicion(minimo, nombre, nombre_simbolo, nombre_aux);
        }
    }

    /*PARTE DE LOS FREES*/
    for (i = 0; i < estados; i++)
    {
        free(matriz[i]);
    }
    free(matriz);

    for (i = 0; subconjuntos[i] != NULL; i++)
    {
        free_conjunto(subconjuntos[i]);
    }
    free(subconjuntos);

    AFNDElimina(determinista);

    return minimo;
}

transicion **AFND_obtener_tabla_transicion(AFND *AFND, int *n_estados)
{
    transicion **tabla_transicion; /*Array de transiciones*/
    transicion *transicion_aux;
    int ini, i, j, count, condicion, n_transiciones = 1;
    int n_simbolos;
    int *estados_ini, *estados_aux; /*Arrays de estados*/
    int **estados_pendientes;       /*Array de estados a analizar*/
    int estado_revisado = 0;        /*Estado que estamos analizando*/
    int len_estados = 1;

    if (AFND == NULL)
    {
        return NULL;
    }

    /*INICIALIZACIONES*/
    n_simbolos = AFNDNumSimbolos(AFND);
    estados_pendientes = (int **)malloc(sizeof(int *));
    estados_pendientes[0] = NULL;
    tabla_transicion = (transicion **)malloc(sizeof(transicion *));
    tabla_transicion[0] = NULL;

    /*Primero cogemos el estado inicial y vemos a cuales transita con lambda*/
    ini = AFNDIndiceEstadoInicial(AFND);
    estados_ini = get_lambda_transition(AFND, ini);

    /*Metemos en la lista a analizar a estados_ini*/
    len_estados++;
    estados_pendientes = realloc(estados_pendientes, len_estados * sizeof(int *));
    estados_pendientes[len_estados - 2] = estados_ini;
    estados_pendientes[len_estados - 1] = NULL;
    condicion = 0;
    /*Bucle principal*/
    while (estados_pendientes[estado_revisado] != NULL)
    {
        /*Miramos las posibles transiciones*/
        for (i = 0; i < n_simbolos; i++)
        {
            count = contar_array(estados_pendientes[estado_revisado]);
            estados_aux = get_estados_destino_with_lambdas(AFND, estados_pendientes[estado_revisado], count, i);

            /*añadimos el resultado al array de pendientes*/
            condicion = 0;
            if (estados_aux != NULL)
            {
                /*Primero lo añado a las transiciones*/
                transicion_aux = transicion_new(estados_pendientes[estado_revisado], i, estados_aux);
                n_transiciones++;
                tabla_transicion = realloc(tabla_transicion, n_transiciones * sizeof(transicion *));
                tabla_transicion[n_transiciones - 2] = transicion_aux;
                tabla_transicion[n_transiciones - 1] = NULL;

                /*Si transiciona lo añadimos al array que revisa*/
                /*comprobar que el array no estaba antes*/
                for (j = 0; estados_pendientes[j] != NULL && condicion == 0; j++)
                {
                    if (is_content_equal(estados_aux, estados_pendientes[j]))
                    {
                        condicion = 1;
                    }
                }

                if (condicion == 0)
                {
                    len_estados++;
                    estados_pendientes = realloc(estados_pendientes, len_estados * sizeof(int *));
                    estados_pendientes[len_estados - 2] = estados_aux;
                    estados_pendientes[len_estados - 1] = NULL;
                }
                else if (j - 1 == estado_revisado)
                {
                    free(estados_aux);
                    free(tabla_transicion[n_transiciones - 2]);
                    transicion_aux = transicion_new(estados_pendientes[j - 1], i, estados_pendientes[j - 1]);

                    tabla_transicion[n_transiciones - 2] = transicion_aux;
                }
            }
        }
        estado_revisado++;
    }
    *n_estados = estado_revisado;

    free(estados_pendientes);
    return tabla_transicion;
}

void calcular_matriz(AFND *original, int **matriz)
{
    int size, i, j;
    int check;

    if (original == NULL || matriz == NULL)
    {
        return;
    }

    /*Reservamos memoria para cada subcojunto posible(no será mayor que el número de estados)*/

    /*Cantidad de estados en el conjunto inicial. Para el bucle*/
    size = AFNDNumEstados(original);

    do
    {
        check = 0;
        for (i = 0; i < size; i++)
        {
            for (j = i + 1; j < size; j++)
            {
                check += comprobar_distinguibles(original, matriz, i, j);
            }
        }
    } while (check != 0);

    return;
}

conjunto **get_subconjuntos(int **matriz, int dimension_matriz)
{

    conjunto **subconjuntos;
    int num_subconjuntos, num_estados;
    int flag_added;
    int i, j;
    int *estados_aux;

    if (matriz == NULL)
    {
        return NULL;
    }

    /*Partimos de que minimo tiene que haber un estado en al minimo equivalente*/
    num_subconjuntos = 0;
    subconjuntos = (conjunto **)calloc(num_subconjuntos + 1, sizeof(conjunto *));
    subconjuntos[num_subconjuntos] = NULL;

    /*Bucle que permite obtener un conjunto en concreto*/
    for (i = 0; i < dimension_matriz; i++)
    {
        flag_added = 0;
        /*Primero de todo verificamos que el estado en concreto no esta en ningun subestado anterior*/
        for (j = 0; subconjuntos[j] != NULL; j++)
        {
            estados_aux = conjunto_get_estados(subconjuntos[j]);
            if (isInArrayEstados(estados_aux, i, conjunto_get_cantidad(subconjuntos[j])) == 1)
            {
                flag_added = 1;
            }
        }
        if (flag_added == 0)
        {
            estados_aux = (int *)calloc(2, sizeof(int));
            num_estados = 1;
            estados_aux[0] = i;
            estados_aux[1] = -1;
            for (j = i + 1; j < dimension_matriz; j++)
            {

                /*Si la matriz en la posicion i,j tiene un 0 significa que los estados son indistinguibles*/
                if (matriz[i][j] == 0)
                {
                    num_estados++;
                    estados_aux = realloc(estados_aux, (num_estados + 1) * sizeof(int));
                    estados_aux[num_estados - 1] = j;
                    estados_aux[num_estados] = -1;
                }
            }
            /*Ahora creamos el nuevo subestado*/
            num_subconjuntos++;
            subconjuntos = realloc(subconjuntos, (num_subconjuntos + 1) * sizeof(conjunto *));
            subconjuntos[num_subconjuntos - 1] = new_conjunto(estados_aux);
            subconjuntos[num_subconjuntos] = NULL;
            free(estados_aux);
        }
    }

    return subconjuntos;
}

int *get_estados_accesibles(AFND *original)
{
    int i, j;
    int ini, n_simbolos, len_accesibles;
    int *estados_accesibles, *estados_aux;
    /*int *estados_inaccesibles = NULL;
    int n_estados, len_inaccesibles = 0;*/

    if (original == NULL)
    {
        return NULL;
    }

    n_simbolos = AFNDNumSimbolos(original);

    /*Los estados iniciales son accesibles seguro*/
    ini = AFNDIndiceEstadoInicial(original);
    estados_accesibles = get_lambda_transition(original, ini);

    /*TODO revisar*/
    for (i = 0; estados_accesibles[i] != -1; i++)
        ;
    len_accesibles = i;

    /*Comprobamos los estados accesibles*/
    /*Cuando termina el bucle, estados_accesibles contiene todos los estados a los que podemos acceder*/
    for (i = 0; estados_accesibles[i] != -1; i++)
    {
        for (j = 0; j < n_simbolos; j++)
        {
            estados_aux = get_estados_destino_with_lambdas(original, estados_accesibles, len_accesibles, j);
            len_accesibles += anadir_estados_array(&estados_accesibles, estados_aux);
            free(estados_aux);
        }
    }

    return estados_accesibles;

    /*estados accesibles contiene los estados accesibles, los inaccesibles son los demas*/
    /* Este bucle cogía los estados inaccesibles. En desuso
    n_estados = AFNDNumEstados(original);
    for (i = 0; i < n_estados; i++)
    {
        if (isInArrayEstados(estados_accesibles, i, len_accesibles) == 0)
        {
            if (estados_inaccesibles == NULL)
            {
                len_inaccesibles = 2;
                estados_inaccesibles = (int *)calloc(len_inaccesibles, sizeof(int));
                estados_inaccesibles[0] = i;
                estados_inaccesibles[1] = -1;
            }
            else
            {
                len_inaccesibles++;
                estados_inaccesibles = realloc(estados_inaccesibles, len_inaccesibles * sizeof(int *));
                estados_inaccesibles[len_inaccesibles - 2] = i;
                estados_inaccesibles[len_inaccesibles - 1] = NULL;
            }
        }
    } */
}

int isInArrayEstados(int *arrayEstados, int number, int tamano)
{
    int i;

    for (i = 0; i < tamano && arrayEstados[i] != -1; i++)
    {
        if (arrayEstados[i] == number)
        {
            return 1;
        }
    }

    return 0;
}

int AFNDContieneEstadoNombre(AFND *AFND, char *nombre)
{
    int nEstados, i;
    nEstados = AFNDNumEstados(AFND);

    for (i = 0; i < nEstados; i++)
    {
        if (strcmp(AFNDNombreEstadoEn(AFND, i), nombre) == 0)
        {
            return i;
        }
    }

    return -1;
}

int *get_estados_destino(AFND *original, int *estado, int n_estados_compruebo, int simbolo)
{
    int n_estados = 0;
    int max_estados;
    int i, j;
    int *estados_final = NULL; /*El conjunto de estados al final*/
    /*Control de errores*/
    if (original == NULL || estado == NULL)
    {
        return NULL;
    }

    max_estados = AFNDNumEstados(original);

    /*Pasamos por todos los estados que quiero comprobar*/
    for (i = 0; i < n_estados_compruebo; i++)
    {

        /*Comprobamos si con el simbolo transiciona a algun estado del original*/
        for (j = 0; j < max_estados; j++)
        {
            /*En el caso de que transicione al simbolo con indice j*/
            if (AFNDTransicionIndicesEstadoiSimboloEstadof(original, estado[i], simbolo, j) == 1)
            {

                /*Si transiciona por primera vez reservamos memoria*/
                if (estados_final == NULL)
                {

                    estados_final = (int *)calloc(1, sizeof(int));
                    estados_final[n_estados] = j;
                    n_estados++;
                }
                else
                {
                    /*Si el estado no lo hemos añadido antes lo añadimos ahora*/
                    if (isInArrayEstados(estados_final, j, n_estados) != 1)
                    {
                        n_estados++;
                        /*redimensionamos la movida*/
                        estados_final = realloc(estados_final, n_estados * (sizeof(int)));
                        estados_final[n_estados - 1] = j;
                    }
                }
            }
        }
    }

    if (n_estados == 0)
    {
        return NULL;
    }
    /*Para recorrer el bucle luego*/
    n_estados++;
    estados_final = realloc(estados_final, n_estados * sizeof(int));
    estados_final[n_estados - 1] = -1;

    return estados_final;
}

int *get_lambda_transition(AFND *original, int estado_input)
{
    int *estados_final = NULL; /*Los estados a los que transiciona*/
    int n_estados = 0;         /*El conjunto de estados que contiene*/
    int estados_max;
    int i;

    if (original == NULL)
    {
        return NULL;
    }

    estados_max = AFNDNumEstados(original);

    AFNDCierraLTransicion(original);

    for (i = 0; i < estados_max; i++)
    {
        if (i != estado_input)
        {
            /*Si el estado a comprobar transiciona al estado con indice i*/
            if (AFNDCierreLTransicionIJ(original, estado_input, i) == 1)
            {
                if (estados_final == NULL)
                {
                    estados_final = (int *)malloc(sizeof(int));
                    estados_final[n_estados] = i;
                    n_estados++;
                }
                else
                {
                    /*redimensionamos la movida*/
                    n_estados++;
                    estados_final = realloc(estados_final, n_estados * sizeof(int));
                    estados_final[n_estados - 1] = i;
                }
            }
        }
    }

    /*Le añado a si mismo*/
    n_estados++;
    estados_final = realloc(estados_final, n_estados * sizeof(int));
    estados_final[n_estados - 1] = estado_input;

    /*Le añado el -1 para conocer el tamaño sin problema*/
    n_estados++;
    estados_final = realloc(estados_final, n_estados * sizeof(int));
    estados_final[n_estados - 1] = -1;

    return estados_final;
}

int *get_estados_destino_with_lambdas(AFND *original, int *estado, int n_estados_compruebo, int simbolo)
{

    int *estados_output;
    int *estados_lambda_aux;
    int *estados_output_aux;
    int i, check_loop;

    if (original == NULL || estado == NULL)
    {
        return NULL;
    }

    /*Los estados a los que se transiciona mediante el simbolo*/
    estados_output_aux = get_estados_destino(original, estado, n_estados_compruebo, simbolo);
    estados_output = get_estados_destino(original, estado, n_estados_compruebo, simbolo);
    if (estados_output == NULL)
    {
        return NULL;
    }
    /*Comprobamos los esget_estados_destino_with_lambdastados a los que se tranciona via lambda*/
    do
    {
        check_loop = 0;
        for (i = 0; estados_output_aux[i] != -1; i++)
        {
            estados_lambda_aux = get_lambda_transition(original, estados_output_aux[i]);
            if (anadir_estados_array(&estados_output, estados_lambda_aux) > 0)
            {
                check_loop = 1;
            }
            free(estados_lambda_aux);
        }

        if (check_loop == 1)
        {
            free(estados_output_aux);
            estados_output_aux = copiar_array(estados_output);
        }

    } while (check_loop == 1);

    free(estados_output_aux);
    return estados_output;
}

int comprobar_distinguibles(AFND *original, int **matriz, int estado_1, int estado_2)
{
    int transicion_1, transicion_2;
    int n_simbolos;
    int i;
    int *aux;

    if (original == NULL || matriz == NULL || estado_1 < 0 || estado_2 < 0)
    {
        return -1;
    }

    n_simbolos = AFNDNumSimbolos(original);

    /*Vemos la transicion de los estados por cada simbolo del automata*/
    for (i = 0; i < n_simbolos; i++)
    {
        aux = get_estados_destino(original, &estado_1, 1, i);
        transicion_1 = aux[0];
        free(aux);

        aux = get_estados_destino(original, &estado_2, 1, i);
        transicion_2 = aux[0];
        free(aux);

        /*Si el resultado es distinguible, entonces los estados son distinguibles*/
        if (matriz[transicion_1][transicion_2] == 1)
        {
            if (matriz[estado_1][estado_2] == 0)
            {
                matriz[estado_1][estado_2] = 1;
                matriz[estado_2][estado_1] = 1;
                return 1;
            }
            return 0;
        }
    }

    /*Si no ha saltado en el bucle, entonces son indistinguibles*/
    return 0;
}

/*Check Pending*/
int anadir_estados_array(int **estados_ini, int *estados_extra)
{
    int i, j;
    int ret = 0;
    int no_contiene = 1;
    int estados_ini_aux, n_estados_extra;
    int *estados_pointer = NULL;

    if (estados_ini == NULL || estados_extra == NULL)
    {
        return 0;
    }

    /*Cogemos el numero de estados al principio y al final*/
    for (i = 0; (*estados_ini)[i] != -1; i++)
        ;
    estados_ini_aux = i + 1;

    for (i = 0; estados_extra[i] != -1; i++)
        ;
    n_estados_extra = i + 1;

    /*recorremos el conjunto de estados al final*/
    for (i = 0; i < n_estados_extra; i++)
    {
        no_contiene = 1;
        /*Vemos si el conjunto de estados ini lo contiene*/
        for (j = 0; j < estados_ini_aux && no_contiene == 1; j++)
        {
            /*En el caso de que lo contenga no hay nada que hacer*/
            if ((*estados_ini)[j] == estados_extra[i])
            {
                no_contiene = 0;
            }
        }
        /*Si no lo contenia lo aniadimos*/
        if (no_contiene == 1)
        {
            estados_ini_aux++;
            estados_pointer = realloc((*estados_ini), estados_ini_aux * sizeof(int));
            *estados_ini = estados_pointer;
            (*estados_ini)[estados_ini_aux - 2] = estados_extra[i];
            (*estados_ini)[estados_ini_aux - 1] = -1;
            ret++;
        }

        no_contiene = 1;
    }
    return ret;
}

/*Tira guay*/
int *copiar_array(int *array_original)
{
    int i, size;
    int *new_array = NULL;

    size = contar_array(array_original);

    new_array = (int *)calloc((size + 1), sizeof(int));

    for (i = 0; i < size; i++)
    {
        new_array[i] = array_original[i];
    }

    new_array[i] = -1;

    return new_array;
}

int contar_array(int *array_original)
{
    int count;

    if (array_original == NULL)
    {
        return 0;
    }

    for (count = 0; array_original[count] != -1; count++)
        ;

    return count;
}

int is_content_equal(int *array_1, int *array_2)
{
    int count1, count2, i;

    if (array_1 == NULL || array_2 == NULL)
    {
        return 0;
    }

    count1 = contar_array(array_1);
    count2 = contar_array(array_2);

    if (count1 != count2)
    {
        return 0;
    }

    for (i = 0; i < count1; i++)
    {
        if (isInArrayEstados(array_2, array_1[i], count1) == 0)
        {
            return 0;
        }
    }

    return 1;
}

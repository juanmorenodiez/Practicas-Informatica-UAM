#include <stdio.h>
#include <stdlib.h>

#include "conjunto.h"

struct _conjunto
{
    int *estados; /*Array de estados en el conjunto*/
    int cantidad; /*cantidad de estados en el conjunto*/
};

conjunto *new_conjunto(int *estados)
{
    int i, size;
    int *nuevos_estados;
    conjunto *new_conjunto;

    if (estados == NULL)
    {
        return NULL;
    }

    for (size = 0; estados[size] != -1; size++)
        ;

    nuevos_estados = (int *)calloc(size, sizeof(int));

    for (i = 0; i < size; i++)
    {
        nuevos_estados[i] = estados[i];
    }

    new_conjunto = (conjunto *)malloc(sizeof(conjunto));

    new_conjunto->estados = nuevos_estados;
    new_conjunto->cantidad = size;

    return new_conjunto;
}

void free_conjunto(conjunto *conjunto)
{
    if (conjunto == NULL)
    {
        return;
    }
    free(conjunto->estados);
    free(conjunto);

    return;
}

int conjunto_get_cantidad(conjunto *conjunto)
{
    if (conjunto == NULL)
    {
        return -1;
    }
    return conjunto->cantidad;
}

int *conjunto_get_estados(conjunto *conjunto)
{
    if (conjunto == NULL)
    {
        return NULL;
    }
    return conjunto->estados;
}

void conjunto_set_estados(conjunto *conjunto, int *nuevos_estados)
{
    if (conjunto == NULL || nuevos_estados == NULL)
    {
        return;
    }

    free(conjunto->estados);
    conjunto->estados = nuevos_estados;

    return;
}

void conjunto_set_cantidad(conjunto *conjunto, int nueva_cantidad)
{
    if (conjunto == NULL)
    {
        return;
    }

    conjunto->cantidad = nueva_cantidad;

    return;
}

void conjunto_eliminar_estado(conjunto *conjunto, int estado)
{
    int *nuevos_estados, *antiguos_estados;
    int i, aux, size;
    if (conjunto == NULL)
    {
        return;
    }

    size = conjunto_get_cantidad(conjunto);
    antiguos_estados = conjunto_get_estados(conjunto);

    nuevos_estados = (int *)calloc(size - 1, sizeof(int));

    for (i = 0, aux = 0; i < size; i++)
    {
        if (antiguos_estados[i] != estado)
        {
            nuevos_estados[aux] = antiguos_estados[i];
            aux++;
        }
    }

    conjunto_set_estados(conjunto, nuevos_estados);
    conjunto_set_cantidad(conjunto, size - 1);

    return;
}

void conjunto_add_estado(conjunto *conjunto, int new_estado)
{
    if (conjunto == NULL || new_estado < 0)
    {
        return;
    }

    conjunto->cantidad++;
    conjunto->estados = realloc(conjunto->estados, conjunto->cantidad * sizeof(int *));
    conjunto->estados[conjunto->cantidad] = new_estado;

    return;
}

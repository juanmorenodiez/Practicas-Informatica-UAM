/**
 * @brief Define la interfaz de cad.c
 *
 * @file cad.h
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0
 * @date 30-04-2019
 * @copyright GNU Public License
 */

#ifndef CAD_H
#define CAD_H

char* cadena_ini();

void cadena_free(char *cadena);

char* cadena_copy(char *cadena);

int cadena_cmp(char *cad1, char *cad2);

int cadena_print(FILE *f, char *cadena);

#endif

/**
 * @brief Define la interfaz de int.c
 *
 * @file int.h
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0
 * @date 15-04-2019
 * @copyright GNU Public License
 */

#ifndef INT_H
#define INT_H


int* int_ini();

void int_destroy(int* dato);

int* int_copy(int* dato);

int int_cmp(int* dato1, int* dato2);

int int_print(FILE* pf, int* dato);

#endif

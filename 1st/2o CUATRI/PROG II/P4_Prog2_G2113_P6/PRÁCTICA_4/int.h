#ifndef INT_H
#define INT_H

int* int_ini();

void int_destroy(int* dato);

int* int_copy(int* dato);

int int_cmp(int* dato1, int* dato2);

int int_print(FILE* pf, int* dato);

#endif

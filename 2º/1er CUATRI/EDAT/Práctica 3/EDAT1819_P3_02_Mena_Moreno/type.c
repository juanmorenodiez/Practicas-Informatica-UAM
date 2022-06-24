#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"

int
value_cmp(type_t type, void* value1, void* value2) {
    switch(type) {
        case INT:
            return *((int*) value1) - *((int*) value2);

        case DBL:
            return *((double*) value1) - *((double*) value2);

        case LLNG:
            return *((long long int*) value1) - *((long long int*) value2);

        case STR:
            return strcmp((char*) value1, (char*) value2);
        default:
            return 0;
    }
}


size_t
value_length(type_t type, void* value) {
    switch(type) {
        case INT:
            return sizeof(int);

        case DBL:
            return sizeof(double);

        case LLNG:
            return sizeof(long long int);

        case STR:
            return (strlen((char*) value) + 1) * sizeof(char);

        default:
            return 0;
    }
}

void
print_value(FILE* f, type_t type, void* value) {
    switch(type) {
        case INT:
            fprintf(f, "Integer:%6d\t", *((int*) value));
            break;

        case DBL:
            fprintf(f, "Double precision:%.3lf\t", *((double*) value));
            break;

        case LLNG:
            fprintf(f, "Long long value:%lli\t", *((long long int*) value));
            break;

        case STR:
            fprintf(f, "String:%s\t", (char*) value);
            break;
    }
}

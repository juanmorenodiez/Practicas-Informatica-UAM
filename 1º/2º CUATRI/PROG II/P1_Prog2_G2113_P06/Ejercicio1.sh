#!/bin/bash

if [ $# -ne 5 ]; then
	echo "El programa necesita todos los nombres de archivos"
	echo ""
	echo "Sintaxis: $0 p1_e1.c p1_e2.c p1_e3.c graph.c nodo.c"
	exit 1
fi

gcc -c -Wall -pedantic -ansi $1

gcc -c -Wall -pedantic -ansi $2

gcc -c -Wall -pedantic -ansi $3

gcc -c -Wall -pedantic -ansi $4

gcc -c -Wall -pedantic -ansi $5

gcc -o p1_e1 p1_e1.o nodo.o 

gcc -o p1_e2 p1_e2.o nodo.o graph.o

gcc -o p1_e3 p1_e3.o nodo.o graph.o

exit 0





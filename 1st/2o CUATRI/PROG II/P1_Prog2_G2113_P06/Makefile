#
#	MACROS
#

CC=gcc
CFLAGS= -g -Wall -pedantic -ansi

all: p1_e1 p1_e2 p1_e3

#
#	EJECUTABLE
#

p1_e1: p1_e1.o nodo.o 
	$(CC) -o p1_e1 p1_e1.o nodo.o 

p1_e2: p1_e2.o nodo.o graph.o
	$(CC) -o p1_e2 p1_e2.o nodo.o graph.o

p1_e3: p1_e3.o nodo.o graph.o
	$(CC) -o p1_e3 p1_e3.o nodo.o graph.o

#
#	OBJETOS
#

p1_e1.o: p1_e1.c
	$(CC) $(CFLAGS) -c p1_e1.c

p1_e2.o: p1_e2.c
	$(CC) $(CFLAGS) -c p1_e2.c

nodo.o: nodo.c nodo.h
	$(CC) $(CFLAGS) -c nodo.c

graph.o: graph.c graph.h 
	$(CC) $(CFLAGS) -c graph.c

p1_e3.o: p1_e3.c
	$(CC) $(CFLAGS) -c p1_e3.c

#
#	BORRAR OBJETOS
#

clean:
	rm -rf *.o ./p1_e2 ./p1_e1 ./p1_e3

#
#	CREACION DE ZIP
#

zip:
	@echo "Creando archivo .zip"
	mkdir P1_Prog2_G2113_P06
	cp *.c *.h Makefile *.pdf *.sh ./P1_Prog2_G2113_P06
	zip -r P1_Prog2_G2113_P06.zip P1_Prog2_G2113_P06
	rm -r P1_Prog2_G2113_P06/

#
#	EJECUTAR CON VALGRIND

#
runv1:
	valgrind --leak-check=full ./p1_e1 

runv2:
	valgrind --leak-check=full ./p1_e2 

runv3:
	valgrind --leak-check=full ./p1_e3

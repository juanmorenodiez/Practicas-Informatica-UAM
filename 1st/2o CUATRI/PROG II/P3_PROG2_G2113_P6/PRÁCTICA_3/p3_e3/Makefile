#
#	MACROS
#

CC=gcc
CFLAGS = -g -Wall -pedantic -ansi -c

all: p3_testqueuel

#
#	EJECUTABLES
#

p3_testqueuel: p3_testqueuel.c nodo.o queuel.o graph.o list.o
	$(CC) -o $@ $^

#
#	OBJETOS	
#

p3_testqueuel.o: p3_testqueuel.c queuel.h nodo.h
	$(CC) $(CFLAGS) $<

nodo.o: nodo.c nodo.h types.h
	$(CC) $(CFLAGS) $<

queuel.o: queuel.c queuel.h types.h
	$(CC) $(CFLAGS) $<

graph.o: graph.c graph.h types.h
	$(CC) $(CFLAGS) $<

list.o: list.c list.h types.h
	$(CC) $(CFLAGS) $<

#
#	VALGRIND
#

runv:
	valgrind --leak-check=full ./p3_testqueuel g1.txt

#
#	BORRADO DE OBJETOS 
#

clean:
	rm -rf *.o

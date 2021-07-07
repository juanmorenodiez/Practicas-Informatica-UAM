#
#	MACROS
#

CC=gcc
CFLAGS = -g -Wall -pedantic -ansi -c

all: p3_e1 p3_e2 p3_testqueue

#
#	EJECUTABLES
#

p3_e1: p3_e1.o nodo.o queue.o graph.o
	$(CC) -o $@ $^

p3_e2: p3_e2.o list.o int.o
	$(CC) -o $@ $^

p3_testqueue: p3_testqueue.o queue.o nodo.o
	$(CC) -o $@ $^
#
#	OBJETOS
#

p3_e1.o: p3_e1.c nodo.h queue.h
	$(CC) $(CFLAGS) $<

p3_e2.o: p3_e2.c list.h
	$(CC) $(CFLAGS) $<

p3_testqueue.o: p3_testqueue.c queue.h nodo.h
	$(CC) $(CFLAGS) $<

nodo.o: nodo.c nodo.h types.h
	$(CC) $(CFLAGS) $<

queue.o: queue.c queue.h types.h
	$(CC) $(CFLAGS) $<

graph.o: graph.c graph.h types.h
	$(CC) $(CFLAGS) $<

list.o: list.c list.h
	$(CC) $(CFLAGS) $<

int.o: int.c int.h
	$(CC) $(CFLAGS) $<
#
#	VALGRIND
#

runv1:
	valgrind --leak-check=full ./p3_e1 g1.txt 1 3

runv1b:
		valgrind --leak-check=full ./p3_testqueue g1.txt

runv2:
		valgrind --leak-check=full ./p3_e2 5

#
#	BORRADO DE OBJETOS
#

clean:
	rm -rf *.o

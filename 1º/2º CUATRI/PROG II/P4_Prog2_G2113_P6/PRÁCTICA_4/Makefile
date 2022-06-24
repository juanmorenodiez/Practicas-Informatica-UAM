#
#	MACROS
#

CC=gcc
CFLAGS = -g -Wall -pedantic -ansi -c

all: p4_e1 p4_e2 p4_test-node-tree p4_e4

#
#	EJECUTABLES
#

p4_e1: p4_e1.o int.o tree.o
	$(CC) -o $@ $^

p4_e2: p4_e2.o int.o tree.o
	$(CC) -o $@ $^

p4_test-node-tree: p4_test-node-tree.o nodo_p4.o tree.o
	$(CC) -o $@ $^

p4_e4: p4_e4.o cad.o tree.o
	$(CC) -o $@ $^

#
#	OBJETOS
#

p4_e1.o: p4_e1.c int.h
	$(CC) $(CFLAGS) $<

p4_e2.o: p4_e2.c int.h
	$(CC) $(CFLAGS) $<

p4_test-node-tree.o: p4_test-node-tree.c nodo.h
	$(CC) $(CFLAGS) $<

p4_e4.o: p4_e4.c cad.h
	$(CC) $(CFLAGS) $<

nodo_p4.o: nodo_p4.c nodo.h types.h
	$(CC) $(CFLAGS) $<

int.o: int.c int.h types.h
	$(CC) $(CFLAGS) $<

cad.o: cad.c cad.h types.h
	$(CC) $(CFLAGS) $<

list.o: list.c list.h
	$(CC) $(CFLAGS) $<

tree.o: tree.c tree.h types.h
	$(CC) $(CFLAGS) $<

#
#	VALGRIND
#

runv:
	valgrind --leak-check=full ./p4_e1 numeros.txt

runv2:
	valgrind --leak-check=full ./p4_e2 numeros.txt

runv3:
	valgrind --leak-check=full ./p4_test-node-tree nodos.txt

runv4:
	valgrind --leak-check=full ./p4_e4 cadenas.txt

#
#	BORRADO DE OBJETOS
#

clean:
	rm -rf *.o

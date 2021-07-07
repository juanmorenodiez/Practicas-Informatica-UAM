#
#	MACROS
#

CC=gcc
CFLAGS= -g -Wall -pedantic -ansi -c

all: p2_e1 p2_e2 p2_e3a p2_e3b p2_e4

1: p2_e1

2: p2_e2

3a: p2_e3a

3b: p2_e3b

4: p2_e4

#
#	EJECUTABLE
#

p2_e1: p2_e1.o nodo.o elestack-node.o stack_elestack.o
	$(CC) -o $@ $^

p2_e2: p2_e2.o elestack-int.o stack_elestack.o
	$(CC) -o $@ $^

p2_e3a: p2_e3a.o nodo.o stack_fp.o elestack-node.o
	$(CC) -o $@ $^

p2_e3b: p2_e3b.o nodo.o stack_fp.o elestack-int.o graph.o
	$(CC) -o $@ $^

p2_e4: p2_e4.o nodo.o graph.o stack_fp.o
	$(CC) -o $@ $^

#
#	OBJETOS
#

p2_e1.o: p2_e1.c stack_elestack.h nodo.h
	$(CC) $(CFLAGS) $<

p2_e2.o: p2_e2.c stack_elestack.h elestack.h
	$(CC) $(CFLAGS) $<

p2_e3a.o: p2_e3a.c nodo.h elestack.h stack_fp.h
	$(CC) $(CFLAGS) $<

p2_e3b.o: p2_e3b.c elestack.h stack_fp.h
	$(CC) $(CFLAGS) $<

p2_e4.o: p2_e4.c graph.h nodo.h stack_fp.h
	$(CC) $(CFLAGS) $<

elestack-node.o: elestack-node.c elestack.h types.h nodo.h
	$(CC) $(CFLAGS) $<

elestack-int.o: elestack-int.c elestack.h types.h
	$(CC) $(CFLAGS) $<

stack_elestack.o: stack_elestack.c stack_elestack.h types.h
	$(CC) $(CFLAGS) $<

nodo.o: nodo.c nodo.h
	$(CC) $(CFLAGS) $<

graph.o: graph.c graph.h stack_fp.h nodo.h types.h
	$(CC) $(CFLAGS) $<

stack_fp.o: stack_fp.c stack_fp.h types.h
	$(CC) $(CFLAGS) $<

runv1:
	valgrind --leak-check=full ./p2_e1

runv2:
	valgrind --leak-check=full ./p2_e2 3

runv3a:
	valgrind --leak-check=full ./p2_e3a

runv3b:
	valgrind --leak-check=full ./p2_e3b 3

runv4:
	valgrind --leak-check=full ./p2_e4 g1.txt 1 3

dist:
	@echo ">>>>>>Making .zip file with all the files"
	rm -f *.o core $(EXE)
	tar cvzf P2_Prog2_G2113_P6.zip Makefile *.c *.h *.pdf

#
#	BORRAR OBJETOS
#

clean:
	rm -rf *.o ./p2_e1 ./p2_e2 ./p2_e3a ./p2_e3b ./p2_e4

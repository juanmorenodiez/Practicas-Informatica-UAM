########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p4_e3
########################################################
OBJECTSP4_E3 = p4_e3.o tree.o nodo_p4.o
########################################################

all: $(EJS) clear

p4_e3: $(OBJECTSP4_E3)
	$(CC) $(CFLAGS) -o p4_e3 $(OBJECTSP4_E3)

p4_e3.o: p4_e3.c tree.h nodo.h
	$(CC) $(CFLAGS) -c p4_e3.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

nodo_p4.o: nodo_p4.c nodo.h
	$(CC) $(CFLAGS) -c nodo_p4.c

clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p4_e3 balanced"
	./p4_e3 dict10.dat B
	@echo ">>>>>>Running p4_e3 non balanced"
	./p4_e3 dict10.dat N

runv:
	@echo ">>>>>>Running p4_e3 balanced with valgrind"
	valgrind --leak-check=full ./p4_e3 dict10.dat B
	@echo ">>>>>>Running p4_e3 non balanced with valgrind"
	valgrind --leak-check=full ./p4_e3 dict10.dat N

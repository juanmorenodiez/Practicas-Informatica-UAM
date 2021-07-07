CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g
LDLIBS = -lodbc

EXE = score suggest test test2 score2 suggest2

all : $(EXE)

clean :
	rm -f *.o *.dat *.txt core $(EXE)

$(EXE) : % : %.o odbc.o table.o type.o index.o

dist:
	@echo ">>>>>>Making .tgz file with all the files"
	tar cvzf EDAT1819_P3_02_Mena_Moreno.tgz Makefile *.c *.h *.pdf

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDLIBS = -lodbc

EXE = appreq appuser apptweet appfollow

all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o odbc.o

dist:
	@echo ">>>>>>Making .tgz file with all the files"
	tar cvzf Andres_Mena_Juan_Moreno.tgz Makefile *.c *.h

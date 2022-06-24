CC = gcc -g -ansi
CFLAGS = -Wall
EXE = main

all : $(EXE)

.PHONY : clean	

$(EXE) : % : %.o afnd.o transformacion.o transicion.o conjunto.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o afnd.o transformacion.o transicion.o conjunto.o

afnd.o : afnd.c afnd.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

transformacion.o : transformacion.c transformacion.h transicion.h conjunto.h afnd.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

transicion.o : transicion.c transicion.h afnd.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

conjunto.o : conjunto.c conjunto.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

clean :
	rm -rf *o
	rm -rf main
	rm -rf *.dot
	rm -rf *.pdf

dot :
	dot -Tpdf minimo.dot -o minimo.pdf
	dot -Tpdf determinista.dot -o determinista.pdf
	dot -Tpdf automata.dot -o no_determinista.pdf

runv:
	valgrind --leak-check=full --track-origins=yes -v ./main
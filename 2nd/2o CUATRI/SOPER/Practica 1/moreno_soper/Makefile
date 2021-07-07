#-----------------------
# IMPORTANTE: Los valores de los parametros de los ejercicio?_test deben ajustarse.
# Se asume que los ficheros fuente se llaman ejercicio1.c, ejercicio2.c,...,ordenar.h
#-----------------------

CC = gcc -std=c99 -pthread
CFLAGS = -Wall
EXE = p1_exercise_3 p1_exercise_5 p1_exercise_7 p1_exercise_9 p1_exercise_11

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o

p1_exercise_3.o : p1_exercise_3.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

p1_exercise_5.o : p1_exercise_5.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

p1_exercise_7.o : p1_exercise_7.c
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

p1_exercise_9.o : p1_exercise_9.c
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<

p1_exercise_11.o : p1_exercise_11.c
		@echo "#---------------------------"
		@echo "# Generando $@"
		@echo "# Depende de $^"
		@echo "# Ha cambiado $<"
		$(CC) $(CFLAGS) -c $<


dist:
	@echo ">>>>>>Making .tgz file with all the files"
	tar cvzf Andres_Mena_Juan_Moreno.tgz Makefile *.c *.h *.pdf nombres.txt

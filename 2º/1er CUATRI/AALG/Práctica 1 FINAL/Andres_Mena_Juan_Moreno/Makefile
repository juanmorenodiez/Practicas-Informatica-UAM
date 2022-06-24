#-----------------------
# IMPORTANTE: Los valores de los parametros de los ejercicio?_test deben ajustarse.
# Se asume que los ficheros fuente se llaman ejercicio1.c, ejercicio2.c,...,ordenar.h
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = ejercicio1 ejercicio2 ejercicio3 ejercicio4 ejercicio5 ejercicio6 ejercicio7

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o ordenacion.o tiempos.o permutaciones.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o ordenacion.o tiempos.o permutaciones.o

permutaciones.o : permutaciones.c permutaciones.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

 ordenacion.o : ordenacion.c ordenacion.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

 tiempos.o : tiempos.c tiempos.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

ejercicio1_test:
	@echo Ejecutando ejercicio1
	@./ejercicio1 -limInf 0 -limSup 9 -numN 10

ejercicio2_test:
	@echo Ejecutando ejercicio2
	@./ejercicio2 -tamanio 4 -numP 6

ejercicio3_test:
	@echo Ejecutando ejercicio3
	@./ejercicio3 -tamanio 3 -numP 5

ejercicio4_test:
	@echo Ejecutando ejercicio4
	@./ejercicio4 -tamanio 10

ejercicio5_test:
	@echo Ejecutando ejercicio5
	@./ejercicio5 -num_min 1000 -num_max 7500 -incr 50 -numP 50 -fichSalida ejercicio5.log

ejercicio6_test:
	@echo Ejecutando ejercicio6
	@./ejercicio6 -tamanio 10

ejercicio7_test:
	@echo Ejecutando ejercicio7
	@./ejercicio7 -num_min 1000 -num_max 7500 -incr 50 -numP 50 -fichSalida ejercicio7.log




dist:
	@echo ">>>>>>Making .tgz file with all the files"
	tar cvzf Andres_Mena_Juan_Moreno.tgz Makefile *.c *.h *.pdf

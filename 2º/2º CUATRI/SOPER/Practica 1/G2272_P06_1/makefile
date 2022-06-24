CC = gcc -g -pthread
CFLAGS = -Wall
EXE = p1_exercise_3 p1_exercise_4 p1_exercise_5 p1_exercise_7 p1_exercise_9 p1_exercise_12
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

p1_exercise_4.o : p1_exercise_4.c
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

dist:
	@echo ">>>>>>Making .tgz file with all the files"
	rm -f *.o core $(EXE)
	tar cvzf 2272_P06_1.tgz makefile *.c *.odt *.pdf *.txt

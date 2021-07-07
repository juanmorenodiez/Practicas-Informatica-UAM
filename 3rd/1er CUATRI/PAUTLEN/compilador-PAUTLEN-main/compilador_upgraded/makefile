CC = gcc
BISON = bison
FLEX = flex
ASM=nasm
ALFA=./alfa

BIN = alfa
CFLAGS = -Wall 

BISONFLAGS = -dyv

ASMFLAGS=-g -f elf32
NASM_LDFLAGS=-m32 -g

OBJ = tablaSimbolos.o hash.o generacion.o

all: ${BIN}

asm: $(BIN) $(NASM_BIN)

alfa: y.tab.o lex.yy.o main.o $(OBJ)
	$(CC) -o $(ALFA) $^

lex.yy.o: lex.yy.c
	$(CC) ${CYYFLAGS} -c -o $@ $<

y.tab.o: y.tab.c
	$(CC) ${CYYFLAGS} -c -o $@ $<

%.o: %.c
	$(CC) ${CFLAGS} -c -o $@ $<

y.tab.c: alfa.y
	$(BISON) $(BISONFLAGS) alfa.y

y.tab.h: alfa.y
	$(BISON) $(BISONFLAGS) alfa.y

lex.yy.c: alfa.l y.tab.h
	$(FLEX) alfa.l

$(NASM_SRC):%.asm: %.alfa
	$(ALFA) $< $@

$(NASM_OBJ):%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

$(NASM_BIN):%: %.o $(NASM_LIB)
	$(CC) $(NASM_LDFLAGS) -o $@ $^

clean:
	@rm -rvf $(BIN) $(OBJ) $(NASM_BIN) $(NASM_OBJ) $(NASM_SRC) lex.yy.c lex.yy.o y.tab.h y.tab.c y.tab.o y.output alfa main.o

	
#@brief Makefile for autocompiling and linking the goose program
#@file makefile
#@author Andrés Mena Godino and Juan Moreno Díez
#@version 2.0
#@date 22-02-2018
###########################################################################################################
vpath %.o ./obj
vpath %.c ./src
vpath %.h ./include
###########################################################################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS= goose set_test die_test
TESTS= inventory_test player_test object_test space_test link_test Sewer_Break
###########################################################################################################
OBJECTSGOOSE= ./obj/command.o ./obj/game.o ./obj/GameManagement.o ./obj/game_loop.o ./obj/graphic_engine.o ./obj/screen.o ./obj/space.o ./obj/object.o ./obj/player.o ./obj/set.o ./obj/die.o ./obj/link.o ./obj/inventory.o ./obj/dialogue.o
OBJECTSSET= ./obj/set_test.o ./obj/set.o
OBJECTSDIE= ./obj/die_test.o ./obj/die.o
OBJECTSLINK= ./obj/link_test.o ./obj/link.o
OBJECTSINVENTORY= ./obj/inventory_test.o ./obj/inventory.o ./obj/set.o
OBJECTSPLAYER= ./obj/player_test.o ./obj/player.o ./obj/inventory.o ./obj/set.o
OBJECTSOBJECT= ./obj/object_test.o ./obj/object.o
OBJECTSSPACE= ./obj/space_test.o ./obj/space.o ./obj/object.o ./obj/set.o
###########################################################################################################
all: $(EJS) $(TESTS)

goose: $(OBJECTSGOOSE)
	$(CC) $(CFLAGS) -o goose $(OBJECTSGOOSE)

set_test: $(OBJECTSSET)
	$(CC) $(CFLAGS) -o set_test $(OBJECTSSET)

die_test: $(OBJECTSDIE)
	$(CC) $(CFLAGS) -o die_test $(OBJECTSDIE)

link_test: $(OBJECTSLINK)
	$(CC) $(CFLAGS) -o link_test $(OBJECTSLINK)

inventory_test: $(OBJECTSINVENTORY)
	$(CC) $(CFLASG) -o inventory_test $(OBJECTSINVENTORY)

player_test: $(OBJECTSPLAYER)
	$(CC) $(CFLAGS) -o player_test $(OBJECTSPLAYER)

object_test: $(OBJECTSOBJECT)
		$(CC) $(CFLAGS) -o object_test $(OBJECTSOBJECT)

space_test: $(OBJECTSSPACE)
		$(CC) $(CFLAGS) -o space_test $(OBJECTSSPACE)

Sewer_Break: ./obj/Sewer_Break.o
	$(CC) $(CFLAGS) -o Sewer_Break ./obj/Sewer_Break.o


##############################################

./obj/Sewer_Break.o: ./src/Sewer_Break.c
	$(CC) $(CFLAGS) -c -Iinclude ./src/Sewer_Break.c -o $@

./obj/link_test.o: ./src/link_test.c ./include/link_test.h ./include/link.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/link_test.c -o $@

./obj/link.o: ./src/link.c ./include/link.h ./include/game.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/link.c -o $@

./obj/inventory_test.o: ./src/inventory_test.c ./include/inventory_test.h ./include/inventory.h ./include/set.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/inventory_test.c -o $@

./obj/player_test.o: ./src/player_test.c ./include/player_test.h ./include/player.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/player_test.c -o $@

./obj/space_test.o: ./src/space_test.c ./include/space_test.h ./include/space.h ./include/set.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/space_test.c -o $@

./obj/object_test.o: ./src/object_test.c ./include/object_test.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/object_test.c -o $@

./obj/inventory.o: ./src/inventory.c ./include/inventory.h ./include/set.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/inventory.c -o $@

./obj/set_test.o: ./src/set_test.c ./include/set.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/set_test.c -o $@

./obj/set.o: ./src/set.c ./include/set.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/set.c -o $@

./obj/die_test.o: ./src/die_test.c ./include/die.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/die_test.c -o $@

./obj/die.o: ./src/die.c ./include/die.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/die.c -o $@

./obj/command.o: ./src/command.c ./include/command.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/command.c -o $@

./obj/game.o: ./src/game.c ./include/game.h ./include/dialogue.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/game.c -o $@

./obj/GameManagement.o: ./src/GameManagement.c ./include/GameManagement.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/GameManagement.c -o $@

./obj/game_loop.o: ./src/game_loop.c ./include/graphic_engine.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/game_loop.c -o $@

./obj/graphic_engine.o: ./src/graphic_engine.c ./include/graphic_engine.h ./include/screen.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/graphic_engine.c -o $@

./obj/screen.o: ./src/screen.c ./include/screen.h
	$(CC) $(CFLAGS) -c -Iinclude -Iinclude ./src/screen.c -o $@

./obj/space.o: ./src/space.c ./include/space.h ./include/types.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/space.c -o $@

./obj/object.o: ./src/object.c ./include/object.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/object.c -o $@

./obj/player.o: ./src/player.c ./include/player.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/player.c -o $@

./obj/dialogue.o: ./src/dialogue.c ./include/dialogue.h
	$(CC) $(CFLAGS) -c -Iinclude ./src/dialogue.c -o $@

###########################################################################################################

document:
	rm -r doc;
	mkdir doc;
	doxygen Doxyfile
	mv latex doc;
	mv html doc;
	firefox ./doc/html/index.html

clean:
	rm -rf *.o $(OBJECTSGOOSE)
	rm -rf *.o $(OBJECTSSET)
	rm -rf *.o $(OBJECTSDIE)
	rm -rf *.o $(OBJECTSLINK)
	rm -rf *.o $(OBJECTSINVENTORY)
	rm -rf *.o $(OBJECTSPLAYER)
	rm -rf *.o $(OBJECTSSPACE)
	rm -rf *.o $(OBJECTSOBJECT)

runv:
	@echo ">>>>>>Running goose with valgrind"
	valgrind --leak-check=full ./goose data.dat

dist:
	@echo ">>>>>>Making .tgz file with all the files"
	tar cvzf I4_PProg_G2191_P2.tgz include src obj doc makefile data.dat graphics.txt Doxyfile Gant+Meeting.pdf Map_and_Objectss.pdf Guide_Sewer_Break.pdf

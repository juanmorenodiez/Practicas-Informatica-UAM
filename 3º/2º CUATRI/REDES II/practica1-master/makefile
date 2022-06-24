CC = gcc -g -pthread
CFLAGS = -Wall
EXE = server client
OBJECTSCLIENT = ./obj/client.o ./obj/libSockets.o
OBJECTSSERVER = ./obj/server.o ./obj/libSockets.o ./obj/pool_thread.o ./obj/picohttpparser.o ./obj/http.o
LIBCONFUSE = -lconfuse

vpath %.o ./obj/
vpath %.c ./src/ ./srclib/
vpath %.h ./includes/

all: $(EXE)

client: $(OBJECTSCLIENT)
	$(CC) $(CFLAGS) -o client $(OBJECTSCLIENT) $(LIBCONFUSE)

server: $(OBJECTSSERVER)
	$(CC) $(CFLAGS) -o server $(OBJECTSSERVER) $(LIBCONFUSE)


./obj/client.o: ./src/client.c ./includes/libSockets.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -Iincludes $< -o $@

./obj/server.o: ./src/server.c ./includes/libSockets.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -Iincludes $< -o $@

./obj/libSockets.o: ./srclib/libSockets.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -Iincludes $< -o $@

./obj/http.o: ./src/http.c ./includes/http.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -Iincludes $< -o $@

./obj/pool_thread.o: ./src/pool_thread.c ./includes/libSockets.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -Iincludes $< -o $@

./obj/picohttpparser.o: ./srclib/picohttpparser.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -Iincludes $< -o $@

./lib/libSockets.a: ./obj/libSockets.o
	@mkdir -p lib
	ar rcs $@ $^

./lib/http.a: ./obj/picohttpparser.o ./obj/http.o
	@mkdir -p lib
	ar rcs $@ $^

./lib/libPoolThreads.a: ./obj/pool_thread.o
	@mkdir -p lib
	ar rcs $@ $^

clean:
	rm -r $(EXE) ./obj ./lib

runv:
	valgrind --leak-check=full --show-leak-kinds=all ./server

compilarLibrerias: all ./lib/libSockets.a ./lib/http.a ./lib/libPoolThreads.a

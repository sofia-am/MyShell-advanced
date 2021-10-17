CC = gcc
CFLAGS = -Wall -Werror -pedantic -g
OBJS = objects
SRC = source
LIB = libraries

all: mkdir main

mkdir:
	mkdir -p $(OBJS) $(LIB)	$(SRC)

main: $(OBJS)/main.o $(OBJS)/dependencies.o
	$(CC) $(OBJS)/main.o $(OBJS)/dependencies.o -o $@

$(OBJS)/dependencies.o: $(SRC)/dependencies.c $(SRC)/dependencies.h
	$(CC) -c $(SRC)/dependencies.c $(CFLAGS) -o $@

$(OBJS)/main.o: main.c $(SRC)/dependencies.h
	$(CC) -c main.c $(CFLAGS) -o $@

clean:
	rm -rf $(OBJS)/*.o  main

CC = gcc
CFLAGS = -Wall -Werror -pedantic -g
OBJS = bin
SRC = src
LIB = lib

all: mkdir main

mkdir:
	mkdir -p $(OBJS) $(LIB)	$(SRC)

main: $(OBJS)/main.o $(OBJS)/interp.o
	$(CC) $(OBJS)/main.o $(OBJS)/interp.o -o $@

$(OBJS)/interp.o: $(SRC)/interp.c $(SRC)/interp.h
	$(CC) -c $(SRC)/interp.c $(CFLAGS) -o $@

$(OBJS)/main.o: main.c $(SRC)/interp.h
	$(CC) -c main.c $(CFLAGS) -o $@

clean:
	rm -rf $(OBJS)/*.o  main

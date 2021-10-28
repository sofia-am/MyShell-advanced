CC = gcc
CFLAGS = -Wall -Werror -pedantic -g
OBJS = bin
SRC = src
LIB = lib

all: mkdir main

mkdir:
	mkdir -p $(OBJS) $(LIB)	$(SRC)

main: $(OBJS)/main.o $(LIB)/libstatic.a
	$(CC) -L. -o $@ $(OBJS)/main.o $(LIB)/libstatic.a -lm

$(LIB)/libstatic.a: $(OBJS)/interp.o $(OBJS)/init.o
	ar rcs $@ $(OBJS)/interp.o $(OBJS)/init.o

$(OBJS)/init.o: $(SRC)/init.c $(SRC)/init.h $(SRC)/interp.h
	$(CC) -c $(SRC)/init.c $(CFLAGS) -o $@

$(OBJS)/interp.o: $(SRC)/interp.c $(SRC)/interp.h 
	$(CC) -c $(SRC)/interp.c $(CFLAGS) -o $@

$(OBJS)/main.o: main.c
	$(CC) -c main.c $(CFLAGS) -o $@

clean:
	rm -rf $(OBJS)/*.o  main

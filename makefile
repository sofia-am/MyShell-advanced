CC = gcc
CFLAGS = -Wall -pedantic -g -Werror
OBJS = bin
SRC = src
LIB = lib

all: mkdir main

mkdir:
	mkdir -p $(OBJS)	$(SRC)

main: $(OBJS)/main.o $(OBJS)/utils.o
	$(CC) -o $@ $(OBJS)/main.o $(OBJS)/utils.o

$(OBJS)/utils.o: $(SRC)/utils.c $(SRC)/utils.h 
	$(CC) -c $(SRC)/utils.c $(CFLAGS) -o $@
	
$(OBJS)/main.o: main.c
	$(CC) -c main.c $(CFLAGS) -o $@

clean:
	rm -rf $(OBJS)/*.o  main
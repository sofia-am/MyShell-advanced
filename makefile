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

$(LIB)/libstatic.a: $(OBJS)/utils.o 
	ar rcs $@ $(OBJS)/utils.o 

$(OBJS)/utils.o: $(SRC)/utils.c $(SRC)/utils.h 
	$(CC) -c $(SRC)/utils.c $(CFLAGS) -o $@
	
$(OBJS)/main.o: main.c
	$(CC) -c main.c $(CFLAGS) -o $@

clean:
	rm -rf $(OBJS)/*.o  main

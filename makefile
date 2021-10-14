CC = gcc
CFLAGS = -Wall -Werror -pedantic
OBJS = objects
SRC = source
LIB = libraries


all: mkdir main

mkdir:
	mkdir -p $(OBJS) $(LIB)	$(SRC)

main: $(OBJS)/main.o $(OBJS)/startup.o
	$(CC) $(OBJS)/main.o $(OBJS)/startup.o -o $@

$(OBJS)/startup.o: $(SRC)/startup.c $(SRC)/startup.h
	$(CC) -c $(SRC)/startup.c $(CFLAGS) -o $@

$(OBJS)/main.o: main.c $(SRC)/startup.h
	$(CC) -c main.c $(CFLAGS) -o $@

clean:
	rm -rf $(OBJS)/*.o  main

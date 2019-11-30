CC = gcc
CFLAGS = -Wall

all: main

main: main.o
	$(CC) -o main main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

run: all
	./main

CC = gcc
CFLAGS =-std=c11 -Wall 

all: main

main: main.o otherlib.o modelib.o
	$(CC) $(CFLAGS) -o main main.o otherlib.o modelib.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c 

otherlib.o: otherlib.c otherlib.h modelib.h
	$(CC) $(CFLAGS) -c otherlib.c otherlib.h modelib.h

modelib.o: modelib.c modelib.h otherlib.h
	$(CC) $(CFLAGS) -c modelib.c otherlib.h modelib.h

run: all
	./main

clean:
	rm -f *.o *.h.gch main

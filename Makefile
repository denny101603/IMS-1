CC = gcc
CFLAGS =-std=c11 -Wall 

all: simulator

simulator: main.o otherlib.o modelib.o
	$(CC) $(CFLAGS) -o simulator main.o otherlib.o modelib.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c 

otherlib.o: otherlib.c otherlib.h modelib.h
	$(CC) $(CFLAGS) -c otherlib.c otherlib.h modelib.h

modelib.o: modelib.c modelib.h otherlib.h loglib.h
	$(CC) $(CFLAGS) -c modelib.c otherlib.h modelib.h loglib.h

loglib.o: loglib.c loglib.h
    $(CC) $(CFLAGS) -c loglib.c loglib.h

run: all
	./simulator imsConf.txt


clean:
	rm -f *.o *.h.gch simulator

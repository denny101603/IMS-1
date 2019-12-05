CC = gcc
CFLAGS =-std=c11 -Wall 

all: simulator

simulator: main.o otherlib.o modelib.o loglib.o
	$(CC) $(CFLAGS) -o simulator main.o otherlib.o modelib.o loglib.o

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

exp1: all
		./simulator exp1a.txt >exp1a.out
		./simulator exp1b.txt >exp1b.out
		./simulator exp1c.txt >exp1c.out
		./simulator exp1d.txt >exp1d.out
		./simulator exp1e.txt >exp1e.out

exp2: all
		./simulator exp2a.txt >exp2a.out
		./simulator exp2b.txt >exp2b.out
		./simulator exp2c.txt >exp2c.out
		./simulator exp2d.txt >exp2d.out

clean:
	rm -f *.o *.h.gch simulator

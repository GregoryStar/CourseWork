CC=gcc -std=c99

all: votecounter

votecounter: votecounter.c makeargv.h
	$(CC) -o votecounter.o votecounter.c makeargv.h

clean:
	rm *.o

CC=gcc -std=gnu99

make: votecounter

votecounter: votecounter.c util.h
	$(CC) -pthread -o votecounter votecounter.c util.h

clean:
	rm $(objects)votecounter

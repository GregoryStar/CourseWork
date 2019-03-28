CC=gcc -std=gnu99

make: server client

server: server.c util.h
	$(CC) -pthread -o server server.c util.h

client: client.c util.h
	$(CC) -o client client.c util.h

clean:
	rm $(objects) server client

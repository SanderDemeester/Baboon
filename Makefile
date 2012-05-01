CC=gcc
NAME=baboon
all:
	baboon
baboon: 

unsecure_client: http.o http_command.o
	$(CC) http.o http_command.o -o http_client
http.o:
	$(CC) -Wall -I. -c unsecure_client/http.c
http_command.o:
	$(CC) -Wall -I. -c http_protocol/http_command.c
clean:
	rm -rf *.o
	rm -rf *.out

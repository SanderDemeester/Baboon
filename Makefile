CC=gcc
all:
	baboon
baboon: 

unsecure_client: http.o http_command.o
	$(CC) http.o http_command.o
http.o:
	$(CC) -Wall -I. -c unsecure_client/http.c
http_command.o
	$(CC) -Wall -I. -c http_protocol/http_command.c
CC=gcc
NAME=baboon
builddir=build/

$(builddir)/%.o: 
all:
	baboon
baboon: 

unsecure_client: http.o http_command.o
	$(CC) http.o http_command.o -o http_client
unsecure_server: http_server.o
	$(CC) http_server.o -o http_server
http.o:
	$(CC) -Wall -I. -c unsecure_client/http.c
http_command.o:
	$(CC) -Wall -I. -c http_protocol/http_command.c
http_server.o:
	$(CC) -Wall -lpthread -I. -c unsecure_server/http_server.c
clean:
	rm -rf *.o
	rm -rf *.out
	rm http_client
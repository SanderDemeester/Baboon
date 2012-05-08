CC=gcc
CFLAGS=-Wimplicit-function-declaration
NAME=baboon
builddir=build/

$(builddir)/%.o: 
all:
	baboon
baboon: 

unsecure_client: http.o http_command.o
	$(CC) http.o http_command.o -o http_client
unsecure_server: http_server.o http_parsing.o arguments.o
	$(CC) $(CFLAGS) http_server.o http_parsing.o arguments.o -lpthread -o http_server
http.o:
	$(CC) -Wall -I. -c unsecure_client/http.c
http_command.o:
	$(CC) $(CFLAGS) -Wall -I. -c http_protocol/http_command.c
http_server.o:
	$(CC) $(CFLAGS) -Wall -I. -c unsecure_server/http_server.c
http_parsing.o:
	$(CC) $(CFLAGS) -Wall -I. -c unsecure_server/http_parsing.c
arguments.o:	
	$(CC) $(CFLAGS) -Wall -I. -c unsecure_server/arguments.c
clean:
	rm -rf *.o 
	rm -rf *.out 


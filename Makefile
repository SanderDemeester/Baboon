CC=gcc
CFLAGS=-Wimplicit-function-declaration -std=c99
NAME=baboon
builddir=build/
obj=obj

$(builddir)/%.o: 
all:
	baboon
baboon: 

unsecure_client: http.o http_command.o
	$(CC) http.o http_command.o -o http_client
unsecure_server: http_server.o http_parsing.o arguments.o filegraph.o
	$(CC) $(CFLAGS) http_server.o http_parsing.o arguments.o filegraph.o -lpthread -lxml2 -lm -o http_server
des_test: des.o des_test.o hex.o
	$(CC) hex.o des.o test_DES.o -o des_test
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
filegraph.o:
	$(CC) $(CFLAGS) -Wall -I. -Lso/ -I./libxml -c unsecure_server/filegraph.c
des.o:
	$(CC) $(CFLAGS) -Wall -I. -c des/des.c
des_test.o:
	$(CC) $(CFLAGS) -Wall -I. -c crypto_test/des_test/test_DES.c
hex.o:
	$(CC) $(CFLAGS) -Wall -I. -c crypto_test/hex.c
clean:
	rm -rf *.o 
	rm -rf *.out 


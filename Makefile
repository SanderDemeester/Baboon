CC=gcc
CFLAGS=-Wimplicit-function-declaration -std=c99
NAME=baboon
builddir=build/
OBJ_UNSECURE_SERVER=http_server.o http_parsing.o arguments.o filegraph.o
OBJ_UNSECURE_CLIENT=http.o http_command.o
OBJ_DES=des.o 
OBJ_AES=aes.o
OBJ_DES_TEST=des.o hex.o des_test.o
OBJ_AES_TEST=aes.o hex.o aes_test.o

$(builddir)/%.o: 
all:
	baboon
baboon: 

unsecure_client: $(OBJ_UNSECURE_CLIENT)
	$(CC) $(OBJ_UNSECURE_CLIENT) -o http_client
unsecure_server: $(OBJ_UNSECURE_SERVER);
	$(CC) $(CFLAGS) $(OBJ_UNSECURE_SERVER) -lpthread -lxml2 -lm -o http_server
des_test: $(OBJ_DES_TEST)
	$(CC) $(OBJ_DES_TEST) -o des_test
aes_test: $(OBJ_AES_TEST)
	$(CC) $(OBJ_AES_TEST) -o aes_test
http.o: $(builddir)/%.o : 
	$(CC) -Wall -I. -c unsecure_client/http.c
http_command.o:
	$(CC) $(CFLAGS) -Wall -I. -c header/http_command.h
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
aes.o:
	$(CC) $(CFLAGS) -Wall -I. -c aes/aes.c
des_test.o:
	$(CC) $(CFLAGS) -Wall -I. -c crypto_test/des_test/test_des.c -o des_test.o
aes_test.o:
	$(CC) $(CFLAGS) -Wall -I. -c crypto_test/aes_test/test_aes.c -o aes_test.o
hex.o:
	$(CC) $(CFLAGS) -Wall -I. -c crypto_test/hex.c
clean:
	rm -rf *.o 
	rm -rf *.out 


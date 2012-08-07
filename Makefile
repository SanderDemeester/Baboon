CC=gcc
SRC=src
CRYPT_SOURCE=$(SRC)/cryptografic_algoritmes
CFLAGS=-Wimplicit-function-declaration -std=c99
NAME=baboon
builddir=build/
OBJ_UNSECURE_SERVER=http_server.o http_parsing.o arguments.o filegraph.o usermode_crytphandlers.o
OBJ_UNSECURE_CLIENT=http.o http_command.o
OBJ_DES=des.o 
OBJ_AES=aes.o
OBJ_RC4=rc4.o
OBJ_DES_TEST=des.o hex.o test_des.o
OBJ_AES_TEST=aes.o hex.o test_aes.o
OBJ_RC4_TEST=rc4.o hex.o test_rc4.o
BIN_FILE= test_aes test_des test_rc4 unsecure_server unsecure_client http_server baboon

$(builddir)/%.o: 
all:
	baboon
baboon: 

unsecure_client: $(OBJ_UNSECURE_CLIENT)
	$(CC) $(OBJ_UNSECURE_CLIENT) -o http_client
unsecure_server: $(OBJ_UNSECURE_SERVER);
	$(CC) $(CFLAGS) $(OBJ_UNSECURE_SERVER) -lpthread -lxml2 -lm -o http_server
test_des: $(OBJ_DES_TEST)
	$(CC) $(OBJ_DES_TEST) -o test_des
test_aes: $(OBJ_AES_TEST)
	$(CC) $(OBJ_AES_TEST) -o test_aes
test_rc4: $(OBJ_RC4_TEST)
	$(CC) $(OBJ_RC4_TEST) -o test_rc4
http.o:	
	$(CC) -Wall -I. -c $(SRC)/unsecure_client/http.c
http_command.o:
	$(CC) $(CFLAGS) -Wall -I. -c header/http_command.h
http_server.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(SRC)/unsecure_server/http_server.c 
http_parsing.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(SRC)/unsecure_server/http_parsing.c
arguments.o:	
	$(CC) $(CFLAGS) -Wall -I. -c $(SRC)/unsecure_server/arguments.c
usermode_crytphandlers.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(CRYPT_SOURCE)/usermode_managementcode/usermode_crytphandlers.c
filegraph.o:
	$(CC) $(CFLAGS) -Wall -I. -Lobject_files/ -I src/ -c $(SRC)/unsecure_server/filegraph.c
des.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(CRYPT_SOURCE)/des/des.c
aes.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(CRYPT_SOURCE)/aes/aes.c
rc4.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(CRYPT_SOURCE)/rc4/rc4.c
test_des.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(SRC)/crypto_test/des_test/test_des.c -o test_des.o
test_aes.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(SRC)/crypto_test/aes_test/test_aes.c -o test_aes.o
test_rc4.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(SRC)/crypto_test/rc4_test/test_rc4.c -o test_rc4.o
hex.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(SRC)/crypto_test/hex.c	
huge.o:
	$(CC) $(CFLAGS) -Wall -I. -c $(CRYPT_SOURCE)/rsa/huge.c
clean:
	rm -rf *.o 
	rm -rf *.out 
	@for file in $(BIN_FILE); do \
	if [ -f $$file ]; then \
	rm "$$file"; \
	fi; done

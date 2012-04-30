CC=gcc
all:
	baboon
baboon: http.o
	$(CC) http.o
http.o:
	$(CC) -Wall -I. -c generic/http.c
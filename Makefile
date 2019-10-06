CC = gcc
OBJECT = RLE.c
BINARY = RLE
all: $(BINARY)

RLE: RLE.c
	$(CC) -o RLE RLE.c -Wall -Wextra 


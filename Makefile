CC = gcc
SOURCE = RLE.c
BINARY= RLE
CFLAGS = -Wall -Wextra

RLE: RLE.c
	$(CC) -o $(BINARY) $(SOURCE) $(CFLAGS)


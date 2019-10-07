CC = gcc
TARGET = RLE
CFLAGS = -std=c99 -Wall -Wextra

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 


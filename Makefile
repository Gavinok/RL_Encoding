CC = gcc
TARGET = RLE
CFLAGS = -std=c99 -g -Wall -pedantic -Wextra

all: RLE

RLE: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 

clean:
		rm -f $(TARGET)

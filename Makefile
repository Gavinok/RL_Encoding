CC = gcc
TARGET = RLE
CFLAGS = -g

all: RLE

RLE: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 

install: $(TARGET)
		cp $(BINARY) /usr/bin

clean:
		rm -f $(TARGET)

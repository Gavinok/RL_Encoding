CC = gcc
TARGET = RLE
CFLAGS = 

all: RLE

RLE: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 

clean:
		rm -f $(TARGET)

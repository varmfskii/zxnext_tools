TARGET = crcbldr
CC = gcc
CFLAGS = -Wall -Os

all: $(TARGET)

$(TARGET).exe: crcbldr.c
	$(CC) $(CFLAGS) -s -o $@ $<

.PHONY: clean
clean:
	rm -rf $(TARGET)

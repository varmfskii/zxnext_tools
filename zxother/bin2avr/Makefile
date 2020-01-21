TARGET = bin2avr
CC = gcc
CFLAGS = -Wall -Os

all: $(TARGET)

$(TARGET): bin2avr.c
	$(CC) $(CFLAGS) -s -o $@ $<

.PHONY: clean
clean:
	rm -rf $(TARGET)

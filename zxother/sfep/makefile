TARGET = sfep
CC = gcc
CFLAGS = -Wall -Os

all: $(TARGET)

$(TARGET).exe: sfep.c
	$(CC) $(CFLAGS) -s -o $@ $<

.PHONY: clean
clean:
	rm -rf $(TARGET)

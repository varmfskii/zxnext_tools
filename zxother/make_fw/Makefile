TARGET = make_fw
CC = gcc

CFLAGS = -Wall -Os

OBJECT = make_fw.o

all: $(TARGET)

## Compile
$(OBJECT): make_fw.c
	$(CC) $(CFLAGS) -o $@ -c $<

##Link
$(TARGET): $(OBJECT)
	 $(CC) $< -o $@


## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECT) $(TARGET)


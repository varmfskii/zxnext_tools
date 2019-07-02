OBJS=client.o

all: client

client: $(OBJS)
	gcc -o $@ $^

client.o: client.c

.PHONY: clean distclean

clean:
	rm -f $(OBJS) *~

distclean: clean
	rm -f client

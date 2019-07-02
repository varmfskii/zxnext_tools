OBJS=server.o

all: server

server: $(OBJS)
	gcc -o $@ $^

server.o: server.c

.PHONY: clean distclean

clean:
	rm -f $(OBJS) *~

distclean: clean
	rm -f server

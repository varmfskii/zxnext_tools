sources=client.c backspace.c error.c execute.c finish.c init.c parse.c puthex.c

objects=$(sources:.c=.o)

all: dependencies client

dependencies: $(sources)
	./mkdeps.sh $@ $^

client: $(objects)
	$(CC) -o $@ $^ -lcurses

include dependencies

.PHONY: clean distclean

clean:
	rm -f $(objects) *~

distclean: clean
	rm -f client dependencies

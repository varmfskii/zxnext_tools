OBJS=main.o tsspiffs.o
CFLAGS+=-std=gnu99

tsspiffs: $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) *~

distclean: clean
	rm -f tsspiffs



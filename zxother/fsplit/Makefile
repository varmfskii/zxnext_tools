OBJS=fsplit.o itoa.o
CFLAGS+=-std=gnu99

fsplit: $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) *~

distclean: clean
	rm -f fsplit

OBJS=fsplit.o itoa.o

fsplit: $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) *~

distclean: clean
	rm -f fsplit

OBJS=main.o func.o msg.o stdafx.o
CFLAGS+=-std=gnu99

spgbld: $(OBJS)
	$(CC) -o $@ $^

.PHONY: clean distclean

clean:
	rm -f $(OBJS) *~

distclean: clean
	rm -f spgbld

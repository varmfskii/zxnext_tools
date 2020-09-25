OBJS=tga2ts.o upcase.o findstr.o
CFLAGS+=-std=gnu99

tga2ts: $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) *~

distclean: clean
	rm -f tga2ts


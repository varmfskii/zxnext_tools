OBJS=tga2ts.o upcase.o findstr.o

tga2ts: $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) *~

distclean: clean
	rm -f tga2ts


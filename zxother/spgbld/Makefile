OBJS=main.o func.o msg.o stdafx.o

spgbld: $(OBJS)
	$(CC) -o $@ $^

.PHONY: clean distclean

clean:
	rm -f $(OBJS) *~

distclean: clean
	rm -f spgbld

CC=gcc
CFLAGS=-O3 -Wall
OBJS=getpalette.o rgb2pal.o writeasm.o support.a
getpalette : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

getpalette.o : getpalette.c getpalette.h
rgb2pal.o : rgb2pal.c getpalette.h
writeasm.o : writeasm.c getpalette.h

support.a : ../support/support.a
	cp ../support/support.a .

../support/support.a : support

getpalette.h : ../support/support.h
	touch $@

.PHONY : clean distclean support

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f getpalette

support :
	make -C ../support

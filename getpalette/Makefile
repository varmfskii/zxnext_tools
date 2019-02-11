CC=gcc
CFLAGS=-O3 -Wall
OBJS=getpalette.o rgb2pal.o writepal.o support.a
getpalette : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

getpalette.o : getpalette.c getpalette.h ../support/support.h
rgb2pal.o : rgb2pal.c getpalette.h
writepal.o : writepal.c getpalette.h
support.a : support

.PHONY : clean distclean support

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f getpalette

support :
	make -C ../support
	cp ../support/support.a .

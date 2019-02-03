CC=gcc
CFLAGS=-O3 -Wall

getpalette : getpalette.o readppm.o rgb2pal.o writepal.o
	$(CC) -o $@ $^ -lnetpbm

getpalette.o : getpalette.c getpalette.h support.h
rgb2pal.o : rgb2pal.c getpalette.h
writepal.o : writepal.c getpalette.h
readppm.o : support
support.h : support

.PHONY : clean distclean support

clean :
	rm -f *.o support.h *~

distclean : clean
	rm -f getpalette

support :
	make -C ../support
	cp ../support/readppm.o ../support/support.h .

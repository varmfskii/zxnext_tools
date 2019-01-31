CC=gcc
CFLAGS=-O3 -Wall

getpalette: getpalette.o readppm.o rgb2pal.o writepal.o
	$(CC) -o $@ $^ -llibpbm

readppm.o : readppm.c getpalette.h
rgb2pal.o : rgb2pal.c getpalette.h
writepal.o : writepal.c getpalette.h

.PHONY : clean distclean

clean :
	rm -f *.o *~

distclean : clean
	rm -f getpalette


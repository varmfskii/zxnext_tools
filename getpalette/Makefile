CC=gcc
CFLAGS=-O3 -Wall
OBJS=getpalette.o rgb2pal.o writeasm.o libzxntools.a
getpalette : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

getpalette.o : getpalette.c getpalette.h
rgb2pal.o : rgb2pal.c getpalette.h
writeasm.o : writeasm.c getpalette.h

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

../libzxntools/libzxntools.a : libzxntools

getpalette.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f getpalette

libzxntools :
	make -C ../libzxntools

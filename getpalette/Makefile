CC=gcc
CFLAGS=-O3 -Wall
OBJS=getpalette.o rgb2pal.o writeasm.o zxntools.a
getpalette : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

getpalette.o : getpalette.c getpalette.h
rgb2pal.o : rgb2pal.c getpalette.h
writeasm.o : writeasm.c getpalette.h

zxntools.a : ../zxntools/zxntools.a
	cp ../zxntools/zxntools.a .

../zxntools/zxntools.a : zxntools

getpalette.h : ../zxntools/zxntools.h
	touch $@

.PHONY : clean distclean zxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f getpalette

zxntools :
	make -C ../zxntools

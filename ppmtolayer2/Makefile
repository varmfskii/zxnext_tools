CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=ppmtolayer2.o writelayer2.o libzxntools.a

ppmtolayer2 : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

ppmtolayer2.o : ppmtolayer2.c ppmtolayer2.h
writelayer2.o : writelayer2.c ppmtolayer2.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

ppmtolayer2.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtolayer2

libzxntools :
	make -C ../libzxntools

CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=ppmtolayer2.o writelayer2.o support.a

ppmtolayer2 : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

ppmtolayer2.o : ppmtolayer2.c ppmtolayer2.h
writelayer2.o : writelayer2.c ppmtolayer2.h
../support/support.a : support

support.a : ../support/support.a
	cp ../support/support.a .

ppmtolayer2.h : ../support/support.h
	touch $@

.PHONY : clean distclean support

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtolayer2

support :
	make -C ../support

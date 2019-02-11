CC=gcc
CFLAGS=-O3 -Wall
OBJS=ppmtolayer2.o writelayer2.o support.a

ppmtolayer2 : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

ppmtolayer2.o : ppmtolayer2.c ppmtolayer2.h ../support/support.h
writelayer2.o : writelayer2.c ppmtolayer2.h
support.a : support

.PHONY : clean distclean support

clean :
	rm -f *.o support.h *~

distclean : clean
	rm -f ppmtolayer2

support :
	make -C ../support
	cp ../support/support.a .

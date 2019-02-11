CC=gcc
CFLAGS=-O3 -Wall
OBJS=ppmtolores.o writelores.o support.a

ppmtolores : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

ppmtolores.o : ppmtolores.c ppmtolores.h ../support/support.h
writelores.o : writelores.c ppmtolores.h
support.a : support

.PHONY : clean distclean support

clean :
	rm -f $(OBJS) *~

distclean : clean
	rm -f ppmtolores

support :
	make -C ../support
	cp ../support/support.a .

CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=ppmtolores.o writelores.o zxntools.a

ppmtolores : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

ppmtolores.o : ppmtolores.c ppmtolores.h
writelores.o : writelores.c ppmtolores.h
../zxntools/zxntools.a : zxntools

zxntools.a : ../zxntools/zxntools.a
	cp ../zxntools/zxntools.a .

ppmtolores.h : ../zxntools/zxntools.h
	touch $@

.PHONY : clean distclean zxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtolores

zxntools :
	make -C ../zxntools

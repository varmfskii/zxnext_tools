CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=ppmtolayer2.o writelayer2.o zxntools.a

ppmtolayer2 : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

ppmtolayer2.o : ppmtolayer2.c ppmtolayer2.h
writelayer2.o : writelayer2.c ppmtolayer2.h
../zxntools/zxntools.a : zxntools

zxntools.a : ../zxntools/zxntools.a
	cp ../zxntools/zxntools.a .

ppmtolayer2.h : ../zxntools/zxntools.h
	touch $@

.PHONY : clean distclean zxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtolayer2

zxntools :
	make -C ../zxntools

CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=layer2toppm.o readlayer2.o zxntools.a

layer2toppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

layer2toppm.o : layer2toppm.c layer2toppm.h
readlayer2.o : readlayer2.c layer2toppm.h
../zxntools/zxntools.a : zxntools

zxntools.a : ../zxntools/zxntools.a
	cp ../zxntools/zxntools.a .

layer2toppm.h : ../zxntools/zxntools.h
	touch $@

.PHONY : clean distclean zxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f layer2toppm

zxntools :
	make -C ../zxntools

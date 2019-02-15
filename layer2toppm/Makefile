CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=layer2toppm.o readlayer2.o support.a

layer2toppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

layer2toppm.o : layer2toppm.c layer2toppm.h
readlayer2.o : readlayer2.c layer2toppm.h
../support/support.a : support

support.a : ../support/support.a
	cp ../support/support.a .

layer2toppm.h : ../support/support.h
	touch $@

.PHONY : clean distclean support

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f layer2toppm

support :
	make -C ../support

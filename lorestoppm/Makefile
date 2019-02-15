CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=lorestoppm.o readlores.o zxntools.a

lorestoppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

lorestoppm.o : lorestoppm.c lorestoppm.h
readlores.o : readlores.c lorestoppm.h
../zxntools/zxntools.a : zxntools

zxntools.a : ../zxntools/zxntools.a
	cp ../zxntools/zxntools.a .

lorestoppm.h : ../zxntools/zxntools.h
	touch $@

.PHONY : clean distclean zxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f lorestoppm

zxntools :
	make -C ../zxntools

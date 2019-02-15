CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=lorestoppm.o readlores.o support.a

lorestoppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

lorestoppm.o : lorestoppm.c lorestoppm.h
readlores.o : readlores.c lorestoppm.h
../support/support.a : support

support.a : ../support/support.a
	cp ../support/support.a .

lorestoppm.h : ../support/support.h
	touch $@

.PHONY : clean distclean support

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f lorestoppm

support :
	make -C ../support

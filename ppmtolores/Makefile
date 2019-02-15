CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=ppmtolores.o writelores.o libzxntools.a

ppmtolores : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

ppmtolores.o : ppmtolores.c ppmtolores.h
writelores.o : writelores.c ppmtolores.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

ppmtolores.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtolores

libzxntools :
	make -C ../libzxntools

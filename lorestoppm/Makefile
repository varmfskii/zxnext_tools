CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS += -O3
endif
OBJS=lorestoppm.o readlores.o libzxntools.a

lorestoppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

lorestoppm.o : lorestoppm.c lorestoppm.h
readlores.o : readlores.c lorestoppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

lorestoppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f lorestoppm

libzxntools :
	make -C ../libzxntools

CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS = -O3
endif
OBJS=sl2toppm.o readsl2.o libzxntools.a

sl2toppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

sl2toppm.o : sl2toppm.c sl2toppm.h
readsl2.o : readsl2.c sl2toppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

sl2toppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f sl2toppm

libzxntools :
	make -C ../libzxntools

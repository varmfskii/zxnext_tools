CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=hicoltoppm.o hicoltorgb.o libzxntools.a

hicoltoppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

hicoltoppm.o : hicoltoppm.c hicoltoppm.h
hicoltorgb.o : hicoltorgb.c hicoltoppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

hicoltoppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f hicoltoppm

libzxntools :
	make -C ../libzxntools

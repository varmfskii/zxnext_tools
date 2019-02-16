CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS = -O3
endif
OBJS=layer2toppm.o readlayer2.o libzxntools.a

layer2toppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

layer2toppm.o : layer2toppm.c layer2toppm.h
readlayer2.o : readlayer2.c layer2toppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

layer2toppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f layer2toppm

libzxntools :
	make -C ../libzxntools

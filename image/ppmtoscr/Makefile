CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=ppmtoscr.o writescr.o libzxntools.a

ppmtoscr : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

ppmtoscr.o : ppmtoscr.c ppmtoscr.h
writescr.o : writescr.c ppmtoscr.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

ppmtoscr.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtoscr

libzxntools :
	make -C ../libzxntools

install: all
	cp ppmtoscr $(PREFIX)/bin/

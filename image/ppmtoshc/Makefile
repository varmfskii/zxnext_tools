CC=gcc
CFLAGS=-Wall
ifeq ($(PAMPREFIX),1)
CFLAGS += -DPAMPREFIX
endif
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=ppmtoshc.o writeshc.o libzxntools.a

ppmtoshc : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

ppmtoshc.o : ppmtoshc.c ppmtoshc.h
writeshc.o : writeshc.c ppmtoshc.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

ppmtoshc.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtoshc

libzxntools :
	make -C ../libzxntools

install: all
	cp ppmtoshc $(PREFIX)/bin/

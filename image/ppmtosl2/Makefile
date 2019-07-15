CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS += -O3
endif
OBJS=ppmtosl2.o writesl2.o libzxntools.a

ppmtosl2 : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

ppmtosl2.o : ppmtosl2.c ppmtosl2.h
writesl2.o : writesl2.c ppmtosl2.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

ppmtosl2.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtosl2

libzxntools :
	make -C ../libzxntools

install:
	cp ppmtosl2 $(PREFIX)/bin/

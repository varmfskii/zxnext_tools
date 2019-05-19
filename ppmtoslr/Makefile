CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=ppmtoslr.o writeslr.o libzxntools.a

ppmtoslr : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

ppmtoslr.o : ppmtoslr.c ppmtoslr.h
writeslr.o : writeslr.c ppmtoslr.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

ppmtoslr.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtoslr

libzxntools :
	make -C ../libzxntools

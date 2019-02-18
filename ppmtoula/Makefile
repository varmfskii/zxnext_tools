CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=ppmtoula.o writeula.o libzxntools.a

ppmtoula : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

ppmtoula.o : ppmtoula.c ppmtoula.h
writeula.o : writeula.c ppmtoula.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

ppmtoula.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtoula

libzxntools :
	make -C ../libzxntools

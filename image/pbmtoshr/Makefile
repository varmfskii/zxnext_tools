CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=pbmtoshr.o bmtoshr.o libzxntools.a

pbmtoshr : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

pbmtoshr.o : pbmtoshr.c pbmtoshr.h
bmtoshr.o : bmtoshr.c pbmtoshr.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

pbmtoshr.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f pbmtoshr

libzxntools :
	make -C ../libzxntools

install: all
	cp pbmtoshr $(PREFIX)/bin

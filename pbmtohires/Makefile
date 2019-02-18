CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=pbmtohires.o bmtohires.o libzxntools.a

pbmtohires : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

pbmtohires.o : pbmtohires.c pbmtohires.h
bmtohires.o : bmtohires.c pbmtohires.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

pbmtohires.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f pbmtohires

libzxntools :
	make -C ../libzxntools

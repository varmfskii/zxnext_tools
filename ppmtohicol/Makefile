CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=ppmtohicol.o writehicol.o libzxntools.a

ppmtohicol : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

ppmtohicol.o : ppmtohicol.c ppmtohicol.h
writehicol.o : writehicol.c ppmtohicol.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

ppmtohicol.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ppmtohicol

libzxntools :
	make -C ../libzxntools

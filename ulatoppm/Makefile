CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=ulatoppm.o ulatorgb.o libzxntools.a

ulatoppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

ulatoppm.o : ulatoppm.c ulatoppm.h
ulatorgb.o : ulatorgb.c ulatoppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

ulatoppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f ulatoppm

libzxntools :
	make -C ../libzxntools

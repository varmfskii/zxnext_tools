CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS += -O3
endif
OBJS=slrtoppm.o readslr.o libzxntools.a

slrtoppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

slrtoppm.o : slrtoppm.c slrtoppm.h
readslr.o : readslr.c slrtoppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

slrtoppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f slrtoppm

libzxntools :
	make -C ../libzxntools

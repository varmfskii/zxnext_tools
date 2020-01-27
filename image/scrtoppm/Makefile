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
OBJS=scrtoppm.o scrtorgb.o libzxntools.a

scrtoppm : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

scrtoppm.o : scrtoppm.c scrtoppm.h
scrtorgb.o : scrtorgb.c scrtoppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

scrtoppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f scrtoppm

libzxntools :
	make -C ../libzxntools

install: all
	cp scrtoppm $(PREFIX)/bin/

CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=shctoppm.o shctorgb.o libzxntools.a

shctoppm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

shctoppm.o : shctoppm.c shctoppm.h
shctorgb.o : shctorgb.c shctoppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

shctoppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f shctoppm

libzxntools :
	make -C ../libzxntools

CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS += -O3
endif
OBJS=paltoasm.o writeasm.o libzxntools.a
paltoasm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

paltoasm.o : paltoasm.c paltoasm.h
writeasm.o : writeasm.c paltoasm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

paltoasm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f paltoasm

libzxntools :
	make -C ../libzxntools

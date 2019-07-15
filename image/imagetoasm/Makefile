CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=imagetoasm.o writeasm.o writepgm.o writeraw.o libzxntools.a
imagetoasm : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

imagetoasm.o : imagetoasm.c imagetoasm.h
writeasm.o : writeasm.c imagetoasm.h
writepgm.o : writepgm.c imagetoasm.h
writeraw.o : writeraw.c imagetoasm.h
../libzxntools/libzxntools.a : libzxntools

imagetoasm.h : ../libzxntools/zxntools.h
	touch $@

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

libzxntools :
	make -C ../libzxntools

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS) *~

distclean : clean
	rm -f imagetoasm

install: all
	cp imagetoasm $(PREFIX)/bin/

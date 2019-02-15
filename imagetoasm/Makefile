CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=imagetoasm.o writeasm.o writepgm.o writeraw.o libzxntools.a
imagetoasm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

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


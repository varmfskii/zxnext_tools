CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=imagetoasm.o writeasm.o writepgm.o writeraw.o support.a
imagetoasm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

imagetoasm.o : imagetoasm.c imagetoasm.h
writeasm.o : writeasm.c imagetoasm.h
writepgm.o : writepgm.c imagetoasm.h
writeraw.o : writeraw.c imagetoasm.h
../support/support.a : support

imagetoasm.h : ../support/support.h
	touch $@

support.a : ../support/support.a
	cp ../support/support.a .

support :
	make -C ../support

.PHONY : clean distclean support

clean :
	rm -f $(OBJS) *~

distclean : clean
	rm -f imagetoasm


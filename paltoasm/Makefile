CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=paltoasm.o writeasm.o support.a
paltoasm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

paltoasm.o : paltoasm.c paltoasm.h
writeasm.o : writeasm.c paltoasm.h
../support/support.a : support

support.a : ../support/support.a
	cp ../support/support.a .

paltoasm.h : ../support/support.h
	touch $@

.PHONY : clean distclean support

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f paltoasm

support :
	make -C ../support

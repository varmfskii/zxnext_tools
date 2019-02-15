CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=paltoasm.o writeasm.o zxntools.a
paltoasm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

paltoasm.o : paltoasm.c paltoasm.h
writeasm.o : writeasm.c paltoasm.h
../zxntools/zxntools.a : zxntools

zxntools.a : ../zxntools/zxntools.a
	cp ../zxntools/zxntools.a .

paltoasm.h : ../zxntools/zxntools.h
	touch $@

.PHONY : clean distclean zxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f paltoasm

zxntools :
	make -C ../zxntools

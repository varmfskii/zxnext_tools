CC=gcc
CFLAGS=-O3 -Wall -g
OBJS=imagetoasm.o writeasm.o writepgm.o writeraw.o zxntools.a
imagetoasm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

imagetoasm.o : imagetoasm.c imagetoasm.h
writeasm.o : writeasm.c imagetoasm.h
writepgm.o : writepgm.c imagetoasm.h
writeraw.o : writeraw.c imagetoasm.h
../zxntools/zxntools.a : zxntools

imagetoasm.h : ../zxntools/zxntools.h
	touch $@

zxntools.a : ../zxntools/zxntools.a
	cp ../zxntools/zxntools.a .

zxntools :
	make -C ../zxntools

.PHONY : clean distclean zxntools

clean :
	rm -f $(OBJS) *~

distclean : clean
	rm -f imagetoasm


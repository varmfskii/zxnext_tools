CC=gcc
CFLAGS=-O3 -Wall
OBJS=img2asm.o writeasm.o writepgm.o writeraw.o support.a
img2asm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

img2asm.o : img2asm.c img2asm.h ../support/support.h
writeasm.o : writeasm.c img2asm.h
writepgm.o : writepgm.c img2asm.h
writeraw.o : writeraw.c img2asm.h
support.a : support

.PHONY : clean distclean support

clean :
	rm -f $(OBJS) *~

distclean : clean
	rm -f test img2asm

support :
	make -C ../support
	cp ../support/support.a .

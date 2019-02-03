CC=gcc
CFLAGS=-O3 -Wall

img2asm : img2asm.o palette.o readppm.o readpal.o rgb2index.o \
	writeasm.o writepgm.o writeraw.o showpal.o
	$(CC) -o $@ $^ -lnetpbm

img2asm.o : img2asm.c img2asm.h support.h
palette.o : palette.c img2asm.h
readpal.o : readpal.c img2asm.h
rgb2index.o : rgb2index.c img2asm.h
showpal.o : showpal.c img2asm.h
test.o : test.c img2asm.h
writeasm.o : writeasm.c img2asm.h
writepgm.o : writepgm.c img2asm.h
writeraw.o : writeraw.c img2asm.h
readppm.o : support
support.h : support

.PHONY : clean distclean support

clean :
	rm -f *.o *~

distclean : clean
	rm -f test img2asm

support :
	make -C ../support
	cp ../support/support.h ../support/readppm.o .

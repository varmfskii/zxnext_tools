CC=gcc

CFLAGS=-O3 -Wall

img2asm: img2asm.o palette.o readimage.o readpal.o rgb2index.o \
	writeasm.o writepgm.o writeraw.o
	$(CC) -o $@ $^ -lnetpbm

test: test.o rgb2index.o writeasm.o palette.o
img2asm.o: img2asm.c img2asm.h
palette.o: palette.c img2asm.h
readimage.o: readimage.c img2asm.h
readpal.o: readpal.c img2asm.h
rgb2index.o: rgb2index.c img2asm.h
test.o: test.c img2asm.h
writeasm.o: writeasm.c img2asm.h
writepgm.o: writepgm.c img2asm.h
writeraw.o: writeraw.c img2asm.h

clean:
	rm -f *.o *~

distclean: clean
	rm -f test img2asm

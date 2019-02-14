CC=gcc
CFLAGS=-Wall -g -O3
OBJS=deallocate.o decimate.o nextpal.o palette.o readixed.o readpal.o \
	readrgb.o rgb2index.o showpal.o writeixed.o writepal.o writergb.o

support.a : $(OBJS)
	ar cr $@ $^

test : test.o support.a
	$(CC) -o $@ $^ -lnetpbm

deallocate.o : deallocate.c support.h
decimate.o : decimate.c support.h
nextpal.o : nextpal.c support.h
palette.o : palette.c support.h
readixed.o : readixed.c support.h
readpal.o : readpal.c support.h
readrgb.o : readrgb.c support.h
rgb2index.o : rgb2index.c support.h
showpal.o : showpal.c support.h
test.o : test.c support.h 
writeixed.o : writeixed.c support.h
writepal.o : writepal.c support.h
writergb.o : writergb.c support.h

.PHONY : clean distclean all

clean :
	rm -f $(OBJS) test.o dec.ppm ixed.pgm ixed.ppm pal.raw rgb.ppm *~

distclean : clean
	rm -f test support.a


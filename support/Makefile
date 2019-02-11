CC=gcc
CFLAGS=-O3 -Wall
OBJS=palette.o readppm.o readpal.o rgb2index.o showpal.o 
all : $(OBJS)

palette.o : palette.c support.h
readppm.o : readppm.c support.h
readpal.o : readpal.c support.h
rgb2index.o : rgb2index.c support.h
showpal.o : showpal.c support.h

.PHONY : clean distclean all

clean :
	rm -f $(OBJS) *~

distclean : clean


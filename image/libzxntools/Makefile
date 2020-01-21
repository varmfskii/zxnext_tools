CC=gcc
CFLAGS = -Wall
ifeq ($(PAMPREFIX),1)
CFLAGS += -DPAMPREFIX
endif
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS += -O3
endif
OBJS=allocate.o col_dist.o deallocate.o decimate.o nextpal.o		\
	palette.o readbm.o readixed.o readpal.o readrgb.o rgb2index.o	\
	showpal.o writebm.o writeixed.o writepal.o writergb.o		\
	writezxn.o zxntoolsver.o

all : libzxntools.a

libzxntools.a : $(OBJS)
	ar cr $@ $^

libzxntools.so : $(OBJS)
	-$(CC) -shared -o $@ $^

test : test.o libzxntools.a
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

col_dist.o : col_dist.c zxntools.h
deallocate.o : deallocate.c zxntools.h
decimate.o : decimate.c zxntools.h
nextpal.o : nextpal.c zxntools.h
palette.o : palette.c zxntools.h
readbm.o : readbm.c zxntools.h
readixed.o : readixed.c zxntools.h
readpal.o : readpal.c zxntools.h
readrgb.o : readrgb.c zxntools.h
rgb2index.o : rgb2index.c zxntools.h
showpal.o : showpal.c zxntools.h
test.o : test.c zxntools.h 
writebm.o : writebm.c zxntools.h
writeixed.o : writeixed.c zxntools.h
writepal.o : writepal.c zxntools.h
writergb.o : writergb.c zxntools.h
writezxn.o : writezxn.c zxntools.h
zxntoolsver.o : zxntoolsver.c zxntools.h

.PHONY : clean distclean all

clean :
	rm -f $(OBJS) test.o dec.ppm ixed.pgm ixed.ppm pal.raw rgb.ppm *~

distclean : clean
	rm -f test libzxntools.a libzxntools.so

install: all
	cp libzxntools.a libzxntools.so $(PREFIX)/libs/

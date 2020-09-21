ifneq ($(IMAGE_MK),1)
include ../image.mk
endif
OBJS=allocate.o col_dist.o deallocate.o decimate.o misc.o palette.o	\
	plus3dos.o readbm.o readpal.o readrgb.o rgb2index.o		\
	writeixed.o writergb.o writezxn.o

ifeq ($(SHARED),1)
all : libzxntools.a libzxntools.so
else
all : libzxntools.a
endif

libzxntools.a : $(OBJS)
	$(AR) cr $@ $^

libzxntools.so : $(OBJS)
	-$(CC) -shared -o $@ $^

test : test.o libzxntools.a
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

col_dist.o : col_dist.c zxntools.h
deallocate.o : deallocate.c zxntools.h
decimate.o : decimate.c zxntools.h
misc.o : misc.c zxntools.h
plus3dos.o : plus3dos.c
palette.o : palette.c zxntools.h
readbm.o : readbm.c zxntools.h
readpal.o : readpal.c zxntools.h
readrgb.o : readrgb.c zxntools.h
rgb2index.o : rgb2index.c zxntools.h
test.o : test.c zxntools.h 
writeixed.o : writeixed.c zxntools.h
writergb.o : writergb.c zxntools.h
writezxn.o : writezxn.c zxntools.h

.PHONY : clean distclean all

clean :
	$(RM) $(OBJS) test.o dec.ppm ixed.pgm ixed.ppm pal.raw rgb.ppm *~

distclean : clean
	$(RM) test libzxntools.a libzxntools.so

install: all
	-$(CP) libzxntools.a libzxntools.so $(PREFIX)/libs/

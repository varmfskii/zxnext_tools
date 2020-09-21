ifneq ($(IMAGE_MK),1)
include ../image.mk
endif
OBJS=ppmtoshc.o writeshc.o libzxntools.a

all: ppmtoshc

ppmtoshc : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

ppmtoshc.o : ppmtoshc.c ppmtoshc.h
writeshc.o : writeshc.c ppmtoshc.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	$(CP) ../libzxntools/libzxntools.a .

ppmtoshc.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) ppmtoshc

libzxntools :
	$(MAKE) -C ../libzxntools

install: all
	$(CP) ppmtoshc $(PREFIX)/bin/

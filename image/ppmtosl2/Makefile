ifneq ($(IMAGE_MK),1)
include ../image.mk
endif
OBJS=ppmtosl2.o libzxntools.a

all: ppmtosl2

ppmtosl2 : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

ppmtosl2.o : ppmtosl2.c ppmtosl2.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	$(CP) ../libzxntools/libzxntools.a .

ppmtosl2.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) ppmtosl2

libzxntools :
	$(MAKE) -C ../libzxntools

install:
	$(CP) ppmtosl2 $(PREFIX)/bin/

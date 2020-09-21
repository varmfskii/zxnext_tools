ifneq ($(IMAGE_MK),1)
include ../image.mk
endif
OBJS=scrtoppm.o scrtorgb.o libzxntools.a

all: scrtoppm

scrtoppm : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

scrtoppm.o : scrtoppm.c scrtoppm.h
scrtorgb.o : scrtorgb.c scrtoppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	$(CP) ../libzxntools/libzxntools.a .

scrtoppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) scrtoppm

libzxntools :
	$(MAKE) -C ../libzxntools

install: all
	$(CP) scrtoppm $(PREFIX)/bin/

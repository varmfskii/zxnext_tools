ifneq ($(IMAGE_MK),1)
include ../image.mk
endif
OBJS=sl2toppm.o readsl2.o libzxntools.a

all: sl2toppm

sl2toppm : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

sl2toppm.o : sl2toppm.c sl2toppm.h
readsl2.o : readsl2.c sl2toppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	$(CP) ../libzxntools/libzxntools.a .

sl2toppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) sl2toppm

libzxntools :
	$(MAKE) -C ../libzxntools

install: all
	$(CP) sl2toppm $(PREFIX)/bin/

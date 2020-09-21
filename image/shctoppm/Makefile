ifneq ($(IMAGE_MK),1)
include ../image.mk
endif
OBJS=shctoppm.o shctorgb.o libzxntools.a

all: shctoppm

shctoppm : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

shctoppm.o : shctoppm.c shctoppm.h
shctorgb.o : shctorgb.c shctoppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	$(CP) ../libzxntools/libzxntools.a .

shctoppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : all clean distclean libzxntools

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) shctoppm

libzxntools :
	$(MAKE) -C ../libzxntools

install: all
	$(CP) shctoppm $(PREFIX)/bin/

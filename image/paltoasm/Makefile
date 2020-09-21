ifneq ($(IMAGE_MK),1)
include ../image.mk
endif
OBJS=paltoasm.o writeasm.o libzxntools.a

all: paltoasm

paltoasm : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

paltoasm.o : paltoasm.c paltoasm.h
writeasm.o : writeasm.c paltoasm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	$(CP) ../libzxntools/libzxntools.a .

paltoasm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : all clean distclean libzxntools

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) paltoasm

libzxntools :
	$(MAKE) -C ../libzxntools

install: all
	$(CP) paltoasm $(PREFIX)/bin/

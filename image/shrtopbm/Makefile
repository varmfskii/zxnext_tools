ifneq ($(IMAGE_MK),1)
include ../image.mk
endif
OBJS=shrtopbm.o shrtobm.o libzxntools.a

all: shrtopbm

shrtopbm : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

shrtopbm.o : shrtopbm.c shrtopbm.h
shrtobm.o : shrtobm.c shrtopbm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	$(CP) ../libzxntools/libzxntools.a .

shrtopbm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) shrtopbm

libzxntools :
	$(MAKE) -C ../libzxntools

install: all
	$(CP) shrtopbm $(PREFIX)/bin/

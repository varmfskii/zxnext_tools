CC=gcc
CFLAGS=-Wall
ifeq ($(PAMPREFIX),1)
CFLAGS += -DPAMPREFIX
endif
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=shrtopbm.o shrtobm.o libzxntools.a

shrtopbm : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

shrtopbm.o : shrtopbm.c shrtopbm.h
shrtobm.o : shrtobm.c shrtopbm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

shrtopbm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f shrtopbm

libzxntools :
	make -C ../libzxntools

install: all
	cp shrtopbm $(PREFIX)/bin/

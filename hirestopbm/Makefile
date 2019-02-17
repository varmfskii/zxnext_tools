CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -g -DDEBUG
else
CFLAGS += -O3
endif
OBJS=hirestopbm.o hirestobm.o libzxntools.a

hirestopbm : $(OBJS)
	$(CC) -o $@ $^ -lnetpbm

hirestopbm.o : hirestopbm.c hirestopbm.h
hirestobm.o : hirestobm.c hirestopbm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	cp ../libzxntools/libzxntools.a .

hirestopbm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f hirestopbm

libzxntools :
	make -C ../libzxntools

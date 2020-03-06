include ../../include.mk
OBJS=slrtoppm.o readslr.o libzxntools.a

slrtoppm : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

slrtoppm.o : slrtoppm.c slrtoppm.h
readslr.o : readslr.c slrtoppm.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	$(CP) ../libzxntools/libzxntools.a .

slrtoppm.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) slrtoppm

libzxntools :
	$(MAKE) -C ../libzxntools

install: all
	$(CP) slrtoppm $(PREFIX)/bin/

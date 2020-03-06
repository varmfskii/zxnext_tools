include ../include.mk
OBJS=ppmtoslr.o writeslr.o libzxntools.a

ppmtoslr : $(OBJS)
	$(CC) -o $@ $^ $(LOPTS) -lnetpbm

ppmtoslr.o : ppmtoslr.c ppmtoslr.h
writeslr.o : writeslr.c ppmtoslr.h
../libzxntools/libzxntools.a : libzxntools

libzxntools.a : ../libzxntools/libzxntools.a
	$(CP) ../libzxntools/libzxntools.a .

ppmtoslr.h : ../libzxntools/zxntools.h
	touch $@

.PHONY : clean distclean libzxntools

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) ppmtoslr

libzxntools :
	$(MAKE) -C ../libzxntools

install: all
	$(CP) ppmtoslr $(PREFIX)/bin/

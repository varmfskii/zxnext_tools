TARGETS=getpalette imagetoasm paltoasm pbmtoshr ppmtoscr ppmtoshc	\
	ppmtosl2 ppmtoslr scrtoppm shctoppm shrtopbm sl2toppm		\
	slrtoppm

all : $(TARGETS) libzxntools
	for file in $(TARGETS); do make -C $$file $$File; done 

.PHONY : $(TARGETS) libzxntools clean distclean install

libzxntools :
	make -C libzxntools

clean :
	for file in $(TARGETS); do make -C $$file clean; done 
	make -C libzxntools clean

distclean : clean
	for file in $(TARGETS); do make -C $$file distclean; done 
	make -C libzxntools distclean

install : all
	mkdir -p $(PREFIX)/bin $(PREFIX)/libs
	for file in $(TARGETS); do cp $$file/$$file $(PREFIX)/bin; done 
	cp libzxntools/libzxntools.a $(PREFIX)/libs
	cp libzxntools/libzxntools.so $(PREFIX)/libs

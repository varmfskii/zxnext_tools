TARGETS=fonttotiles getpalette imagetoasm paltoasm paltoppm pbmtoshr	\
	ppmtoscr ppmtoshc ppmtosl2 scrtoppm shctoppm shrtopbm		\
	sl2toppm


all : $(TARGETS) libzxntools
	for file in $(TARGETS); do make -C $$file $$File || break; done 

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
	rm -f $(PREFIX)/bin/ppmtoslr $(PREFIX)/bin/slrtoppm
	ln -s $(PREFIX)/bin/ppmtosl2 $(PREFIX)/bin/ppmtoslr
	ln -s $(PREFIX)/bin/sl2toppm $(PREFIX)/bin/slrtoppm
	cp libzxntools/libzxntools.a $(PREFIX)/libs
	-cp libzxntools/libzxntools.so $(PREFIX)/libs

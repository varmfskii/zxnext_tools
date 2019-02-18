TARGETS=getpalette hicoltoppm hirestopbm imagetoasm layer2toppm lorestoppm \
	nexcreator paltoasm pbmtohires ppmtohicol ppmtolayer2 ppmtolores \
	ppmtoula ulatoppm

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
	rm -f bin/*

install : all
	mkdir -p bin libs
	for file in $(TARGETS); do cp $$file/$$file bin; done 
	cp libzxntools/libzxntools.a libs
	cp libzxntools/libzxntools.so libs

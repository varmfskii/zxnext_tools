TARGETS=getpalette imagetoasm layer2toppm lorestoppm nexcreator paltoasm \
	ppmtolayer2 ppmtolores

all : $(TARGETS)

.PHONY : $(TARGETS) libzxntools clean distclean install

libzxntools :
	make -C libzxntools

imagetoasm : libzxntools
	make -C imagetoasm imagetoasm

getpalette : libzxntools
	make -C getpalette getpalette

nexcreator :
	make -C nexcreator nexcreator

layer2toppm :
	make -C layer2toppm layer2toppm

lorestoppm :
	make -C lorestoppm lorestoppm

paltoasm :
	make -C paltoasm paltoasm

ppmtolayer2 : libzxntools
	make -C ppmtolayer2 ppmtolayer2

ppmtolores : libzxntools
	make -C ppmtolores ppmtolores

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

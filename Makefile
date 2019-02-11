all : img2asm getpalette

.PHONY: support clean distclean img2asm getpalette nexcreator ppmtolayer2 \
	install

support :
	make -C support

img2asm : support
	make -C img2asm img2asm

getpalette : support
	make -C getpalette getpalette

nexcreator :
	make -C nexcreator nexcreator

ppmtolayer2 : support
	make -C ppmtolayer2 ppmtolayer2

clean :
	make -C img2asm clean
	make -C getpalette clean
	make -C support clean
	make -C nexcreator clean
	make -C ppmtolayer2 clean

distclean : clean
	make -C img2asm distclean
	make -C getpalette distclean
	make -C support distclean
	make -C nexcreator distclean
	make -C ppmtolayer2 distclean
	rm -f bin/*

install : all
	mkdir -p bin
	cp -tbin getpalette/getpalette
	cp -tbin img2asm/img2asm
	cp -tbin nexcreator/nexcreator
	cp -tbin ppmtolayer2/ppmtolayer2

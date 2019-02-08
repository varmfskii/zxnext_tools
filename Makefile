all : img2asm getpalette

.PHONY: support clean distclean img2asm getpalette nexcreator install

support :
	make -C support

img2asm : support
	make -C img2asm img2asm

getpalette : support
	make -C getpalette getpalette

NexCreator :
	make -C nexcreator nexcreator

clean :
	make -C img2asm clean
	make -C getpalette clean
	make -C support clean
	make -C nexcreator clean

distclean : clean
	make -C img2asm distclean
	make -C getpalette distclean
	make -C support distclean
	make -C nexcreator clean
	rm -f bin/*

install : all
	mkdir -p bin
	cp -tbin getpalette/getpalette
	cp -tbin img2asm/img2asm
	cp -tbin nexcreator/nexcreator

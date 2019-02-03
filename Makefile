all : img2asm getpalette

.PHONY: support clean distclean img2asm getpalette

support :
	make -C support

img2asm : support
	make -C img2asm img2asm

getpalette : support
	make -C getpalette getpalette

clean :
	make -C img2asm clean
	make -C getpalette clean

distclean : clean
	make -C img2asm distclean
	make -C getpalette distclean

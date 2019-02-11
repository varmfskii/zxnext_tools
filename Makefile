TARGETS=img2asm getpalette nexcreator ppmtolayer2 ppmtolores

all : $(TARGETS)

.PHONY : $(TARGETS) support clean distclean install

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

ppmtolores : support
	make -C ppmtolores ppmtolores

clean :
	for file in $(TARGETS); do make -C $$file clean; done 
	make -C support clean
distclean : clean
	for file in $(TARGETS); do make -C $$file distclean; done 
	make -C support distclean
	rm -f bin/*

install : all
	mkdir -p bin
	for file in $(TARGETS); do cp $$file/$$file bin; done 

TARGETS=getpalette imagetoasm layer2toppm lorestoppm nexcreator paltoasm \
	ppmtolayer2 ppmtolores

all : $(TARGETS)

.PHONY : $(TARGETS) support clean distclean install

support :
	make -C support

imagetoasm : support
	make -C imagetoasm imagetoasm

getpalette : support
	make -C getpalette getpalette

nexcreator :
	make -C nexcreator nexcreator

layer2toppm :
	make -C layer2toppm layer2toppm

lorestoppm :
	make -C lorestoppm lorestoppm

paltoasm :
	make -C paltoasm paltoasm

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

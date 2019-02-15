TARGETS=getpalette imagetoasm layer2toppm lorestoppm nexcreator paltoasm \
	ppmtolayer2 ppmtolores

all : $(TARGETS)

.PHONY : $(TARGETS) zxntools clean distclean install

zxntools :
	make -C zxntools

imagetoasm : zxntools
	make -C imagetoasm imagetoasm

getpalette : zxntools
	make -C getpalette getpalette

nexcreator :
	make -C nexcreator nexcreator

layer2toppm :
	make -C layer2toppm layer2toppm

lorestoppm :
	make -C lorestoppm lorestoppm

paltoasm :
	make -C paltoasm paltoasm

ppmtolayer2 : zxntools
	make -C ppmtolayer2 ppmtolayer2

ppmtolores : zxntools
	make -C ppmtolores ppmtolores

clean :
	for file in $(TARGETS); do make -C $$file clean; done 
	make -C zxntools clean
distclean : clean
	for file in $(TARGETS); do make -C $$file distclean; done 
	make -C zxntools distclean
	rm -f bin/*

install : all
	mkdir -p bin
	for file in $(TARGETS); do cp $$file/$$file bin; done 

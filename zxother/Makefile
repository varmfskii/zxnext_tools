PREFIX=$(CURDIR)

DIRS=addcrc bin2avr bin2case bin2defb crcbldr csum32 dxt2dxp fsplit	\
	make_fw sdcc-lib-split sfep spgbld spiffs tga2ts tsspiffs

all: build

build: $(DIRS)

$(DIRS): FORCE
	make -C $@

install: build
	mkdir -p $(PREFIX)/bin
	for DIR in $(DIRS);do cp $$DIR/$$DIR $(PREFIX)/bin;done	

inst_par: build
	for DIR in $(DIRS);do cp $$DIR/$$DIR ../bin;done	

clean:
	for DIR in $(DIRS);do make clean -C $$DIR;done

distclean:
	for DIR in $(DIRS);do make distclean -C $$DIR;done

FORCE:

.PHONY: all build $(DIRS) install inst_par clean distclean

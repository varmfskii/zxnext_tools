SRCS=cmds.c net.c senderr.c setbaud.c uart.c

OBJS=$(SRCS:.c=.o)

PREFIX=$(CURDIR)/..

OPT=-clib=sdcc_iy -SO3 --max-allocs-per-node200000 --opt-code-size

DOTN=-create-app -subtype=dotn -startup=30
NEX=-create-app -subtype=nex -startup=5
SNA=-create-app -subtype=sna -startup=5
TAP=-create-app -subtype=tap -startup=5

%.o: %.c
	zcc +zxn -c $(OPT) $<

all: zxnftp.cfg zxnftp.nex zxnftp.sna zxnftp.tap ZXNFTP

zxnftp.cfg:
	cd .. ; ./mkzxnftpcfg.py

zxnftp.sna: zxnftp.c $(OBJS)
	zcc +zxn -o zxnftp -DSNAP $(OPT) $(SNA) $^

zxnftp.nex: zxnftp.c $(OBJS)
	zcc +zxn -o zxnftp -DNEXT $(OPT) $(NEX) $^

zxnftp.tap: zxnftp.c $(OBJS)
	zcc +zxn -o zxnftp -DTAPE $(OPT) $(TAP) $^

ZXNFTP: zxnftp.c $(OBJS)
	zcc +zxn -o zxnftp -DDOTN $(OPT) $(DOTN) $^

cmds.o: cmds.c zxnftp.h
net.o: net.c zxnftp.h
senderr.o: senderr.c zxnftp.h
uart.o: uart.c zxnftp.h

.PHONY: clean distclean install

clean:
	rm -f $(OBJS) zxnftp.o zxnftp_dotn.o *~ zcc_opt.def
	rm -f zxnftp_CODE.bin zxnftp_UNASSIGNED.bin zxnftp_MAIN.bin

distclean: clean
	rm -f zxnftp.nex zxnftp.sna zxnftp.tap ZXNFTP

install: all
	mkdir -p $(PREFIX)/zxnext/dot
	cp zxnftp.nex zxnftp.sna zxnftp.tap zxnftp.cfg $(PREFIX)/zxnext
	cp ZXNFTP $(PREFIX)/zxnext/dot

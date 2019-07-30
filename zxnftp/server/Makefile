SRCS=cmds.c net.c senderr.c setbaud.c uart.c

OBJS=$(SRCS:.c=.o)

PREFIX=$(CURDIR)/..

OPT=-clib=sdcc_iy -SO3 --max-allocs-per-node200000 --opt-code-size
#OPT=-clib=sdcc_iy

DOTN=-create-app -subtype=dotn
NEX=-create-app -subtype=nex
SNA=-create-app -subtype=sna
TAP=-create-app -subtype=tap

%.o: %.c
	zcc +zxn -c $(OPT) $<

all: zxnftp.cfg zxnftp.nex zxnftp.sna zxnftp.tap ZXNFTP

zxnftp.cfg:
	cd .. ; ./mkzxnftpcfg.py

zxnftp.sna: zxnftp.o $(OBJS)
	zcc +zxn -o zxnftp $(OPT) $(SNA) $^

zxnftp.nex: zxnftp.o $(OBJS)
	zcc +zxn -o zxnftp $(OPT) $(NEX) $^

zxnftp.tap: zxnftp.o $(OBJS)
	zcc +zxn -o zxnftp $(OPT) $(TAP) $^

ZXNFTP: zxnftp_dotn.o $(OBJS)
	zcc +zxn -o zxnftp $(OPT) $(DOTN) $^

zxnftp_dotn.o: zxnftp.c zxnftp.h
	zcc +zxn -DDOTN -o zxnftp_dotn.o -c $(OPT) $<

zxnftp.o: zxnftp.c zxnftp.h
cmds.o: cmds.c zxnftp.h
net.o: net.c zxnftp.h
senderr.o: senderr.c zxnftp.h
uart.o: uart.c zxnftp.h

.PHONY: clean distclean install

clean:
	rm -f $(OBJS) *~ zcc_opt.def
	rm -f zxnftp_CODE.bin zxnftp_UNASSIGNED.bin zxnftp_MAIN.bin

distclean: clean
	rm -f zxnftp.nex zxnftp.sna zxnftp.tap ZXNFTP

install: all
	mkdir -p $(PREFIX)/zxnext/dot
	cp zxnftp.nex zxnftp.sna zxnftp.tap zxnftp.cfg $(PREFIX)/zxnext
	cp ZXNFTP $(PREFIX)/zxnext/dot

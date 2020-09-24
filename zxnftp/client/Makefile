sources=zxnftp.c call_get.c call_id.c call_put.c call_simple.c		\
	cmd_baud.c cmd_cat.c cmd_cd.c cmd_dir.c cmd_exit.c cmd_get.c	\
	cmd_help.c cmd_help.c cmd_lcd.c cmd_ls.c cmd_mget.c		\
	cmd_mkdir.c cmd_mput.c cmd_put.c cmd_pwd.c cmd_quit.c		\
	cmd_rm.c cmd_rmdir.c cmd_script.c commands.c execute.c		\
	init.c net.c neterr.c parse.c printing.c util.c


objects=$(sources:.c=.o)

PREFIX=$(CURDIR)/..

ifeq ($(CURSES),1)
CFLAGS+=-DCURSES
endif

all: dependencies zxnftp zxnftp.conf

dependencies: $(sources)
	./mkdeps.sh $@ $^

ifeq ($(CURSES),1)
zxnftp: $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ -lcurses
else
zxnftp: $(objects)
	$(CC) $(LDFLAGS) -o $@ $^
endif

zxnftp.conf:
	cd .. ; ./mkzxnftpcfg.py

include dependencies

.PHONY: clean distclean

clean:
	rm -f $(objects) *~

distclean: clean
	rm -f zxnftp dependencies

install: all
	mkdir -p $(PREFIX)/bin
	cp zxnftp zxnftp.conf $(PREFIX)/bin

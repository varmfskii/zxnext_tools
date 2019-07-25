sources=zxnftp.c call_get.c call_id.c call_put.c call_simple.c		\
	cmd_baud.c cmd_cat.c cmd_cd.c cmd_dir.c cmd_exit.c cmd_get.c	\
	cmd_help.c cmd_help.c cmd_ls.c cmd_mget.c cmd_mkdir.c		\
	cmd_mput.c cmd_put.c cmd_pwd.c cmd_quit.c cmd_rm.c		\
	cmd_rmdir.c commands.c execute.c init.c net.c neterr.c		\
	parse.c util.c


objects=$(sources:.c=.o)

PREFIX=$(CURDIR)/..

all: dependencies zxnftp zxnftp.cfg

dependencies: $(sources)
	./mkdeps.sh $@ $^

zxnftp: $(objects)
	$(CC) -o $@ $^ -lcurses

zxnftp.cfg:
	cd .. ; ./mkzxnftpcfg.py

include dependencies

.PHONY: clean distclean

clean:
	rm -f $(objects) *~

distclean: clean
	rm -f zxnftp dependencies

install: all
	mkdir -p $(PREFIX)/bin
	cp zxnftp zxnftp.cfg $(PREFIX)/bin

OPT=-clib=sdcc_iy -SO3 --max-allocs-per-node200000 --opt-code-size
DOT=-create-app -subtype=dot -startup=30 $(OPT)
TGTS=SHOWSIMG TESTOPTS
OBJS=showsimg.o error.o getext.o getopts.o help.o noattr.o readstate.o \
	remap.o restorestate.o savestate.o setimage.o setpalette.o setstate.o \
	writestate.o

.PHONY: clean distclean all

all: $(TGTS) $(IMGTGT)

SHOWSIMG: $(OBJS)
	 zcc +zxn $(DOT) -o showsimg $^

TESTOPTS: testopts.o
	 zcc +zxn $(DOT) -o testopts $^

%.o: %.c
	zcc +zxn $(OPT) -c $<

%.o: %.asm
	zcc +zxn $(OPT) -c $<

showsimg.o: showsimg.c showsimg.h
error.o: error.c showsimg.h
getext.o: getext.c
getopts.o: getopts.c showsimg.h
guessmode.o: guessmode.c showsimg.h
help.o: help.c
noattr.o: noattr.c
readstate.o: readstate.c showsimg.h
remap.o: remap.c
restorestate.o: restorestate.c showsimg.h zxnext.h
savestate.o: savestate.c showsimg.h zxnext.h
setimage.o: setimage.c showsimg.h
setpalette.o: setpalette.c showsimg.h zxnext.h
setstate.o: setpalette.c showsimg.h zxnext.h
string32.o: string32.c
testopts.o: testopts.c showsimg.h
writestate.o: writestate.c showsimg.h

clean:
	rm -f *~ $(OBJS) testopts.o *.bin maketest

distclean: clean
	rm -f $(IMAGES) $(TGTS)

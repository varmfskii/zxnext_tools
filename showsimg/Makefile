OPT=-clib=sdcc_iy -SO3 --max-allocs-per-node200000 --opt-code-size
DOT=-create-app -subtype=dot -startup=30 $(OPT)
TGTS=SHOWSIMG TESTOPTS
OBJS=showsimg.o getopts.o remap.o state.o setimage.o setpalette.o util.o

.PHONY: clean distclean all

all: $(TGTS) $(IMGTGT)

SHOWSIMG: $(OBJS)
	 zcc +zxn $(DOT) -o showsimg $^

TESTOPTS: testopts.o
	 zcc +zxn $(DOT) -o testopts $^

%.o: %.c
	zcc +zxn $(OPT) -c $<

showsimg.o: showsimg.c showsimg.h
guessmode.o: guessmode.c showsimg.h
remap.o: remap.c
state.o: state.c showsimg.h zxnext.h
setimage.o: setimage.c showsimg.h zxnext.h
setpalette.o: setpalette.c showsimg.h zxnext.h
util.o: util.c showsimg.h
testopts.o: testopts.c showsimg.h

clean:
	rm -f *~ $(OBJS) testopts.o *.bin maketest

distclean: clean
	rm -f $(IMAGES) $(TGTS)

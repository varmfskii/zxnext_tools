OPT=-clib=sdcc_iy -SO3 --max-allocs-per-node200000 --opt-code-size
DOT=-create-app -subtype=dot -startup=30 $(OPT)
TGTS=SHOW
OBJS=show.o guessmode.o state.o setimage.o setpalette.o util.o

.PHONY: clean distclean all

all: $(TGTS) $(IMGTGT)

SHOW: $(OBJS)
	 zcc +zxn $(DOT) -o show $^

%.o: %.c
	zcc +zxn $(OPT) -c $<

show.o: show.c show.h
guessmode.o: guessmode.c show.h
state.o: state.c show.h zxnext.h
setimage.o: setimage.c show.h zxnext.h
setpalette.o: setpalette.c show.h zxnext.h
util.o: util.c show.h

clean:
	rm -f *~ $(OBJS) *.bin maketest

distclean: clean
	rm -f $(IMAGES) $(TGTS)

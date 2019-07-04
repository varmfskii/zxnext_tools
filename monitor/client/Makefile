sources=backspace.c call_exec.c call_exit.c call_query.c call_read.c	\
	call_write.c client.c cmd_ascii.c cmd_bkpt.c cmd_block.c	\
	cmd_byte.c cmd_cont.c cmd_disp.c cmd_edit.c cmd_go.c		\
	cmd_half.c cmd_help.c cmd_inbase.c cmd_load.c cmd_mnem.c	\
	cmd_move.c cmd_outbase.c cmd_quit.c cmd_reg.c cmd_save.c	\
	cmd_sym.c cmd_word.c cmd_yank.c commands.c error.c execute.c	\
	finish.c init.c parse.c puthex.c

objects=$(sources:.c=.o)

all: dependencies client

dependencies: $(sources)
	./mkdeps.sh $@ $^

client: $(objects)
	$(CC) -o $@ $^ -lcurses

include dependencies

.PHONY: clean distclean

clean:
	rm -f $(objects) *~

distclean: clean
	rm -f client dependencies

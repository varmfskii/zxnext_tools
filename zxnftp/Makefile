TARGETS=client server

PREFIX=$(CURDIR)

all : $(TARGETS)
	for tgt in $(TARGETS); do make -C $$tgt all; done

.PHONY : $(TARGETS) clean distclean

clean : $(TARGETS)
	for tgt in $(TARGETS); do make -C $$tgt clean; done

distclean : $(TARGETS)
	for tgt in $(TARGETS); do make -C $$tgt distclean; done

install : $(TARGETS)
	mkdir -p $(PREFIX)/bin $(PREFIX)/zxnext/dot
	for tgt in $(TARGETS); do make -C $$tgt install; done

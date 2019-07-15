TARGETS=image nexcreator

PREFIX=$(CURDIR)

all : $(TARGETS)
	for file in $(TARGETS); do make -C $$file $$File; done 

.PHONY : $(TARGETS) clean distclean install

clean :
	for file in $(TARGETS); do make -C $$file clean; done 

distclean : clean
	for file in $(TARGETS); do make -C $$file distclean; done 

install : all
	mkdir -p $(PREFIX)/bin $(PREFIX)/libs
	for file in $(TARGETS); do make -C $$file install; done

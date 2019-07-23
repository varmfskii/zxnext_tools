TARGETS=image nexcreator zxnftp

PREFIX=$(CURDIR)

all : $(TARGETS)
	for file in $(TARGETS) ;\
	  do make PREFIX=$(PREFIX) -C $$file $$File ;\
	done 

.PHONY : $(TARGETS) clean distclean install

clean :
	for file in $(TARGETS) ;\
	  do make PREFIX=$(PREFIX) -C $$file clean ;\
	done 

distclean : clean
	for file in $(TARGETS) ;\
	  do make PREFIX=$(PREFIX) -C $$file distclean ;\
	done 

install : all
	for file in $(TARGETS) ;\
	  do make PREFIX=$(PREFIX) -C $$file install ;\
	done

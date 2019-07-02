TARGETS=image nexcreator

all : $(TARGETS)
	for file in $(TARGETS); do make -C $$file $$File; done 

.PHONY : $(TARGETS) clean distclean install

clean :
	for file in $(TARGETS); do make -C $$file clean; done 

distclean : clean
	for file in $(TARGETS); do make -C $$file distclean; done 
	rm -f bin/*

install : all
	mkdir -p bin libs
	for file in $(TARGETS); do make -C $$file install; done

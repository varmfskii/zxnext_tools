TARGETS=libzxntools fonttotiles getpalette imagetoasm paltoasm paltoppm	\
	pbmtoshr ppmtoscr ppmtoshc ppmtosl2 scrtoppm shctoppm shrtopbm	\
	sl2toppm
TASKS=all clean distclean
PREFIX=$(CURDIR)

default: all

.PHONY: $(TASKS) install

define doit
$(1): $(1)-$(2)
$(1)-$(2):
	$(MAKE) -C $(2) $(1)
endef

x := $(foreach task, $(TASKS), $(eval y = $(foreach tgt, $(TARGETS), $(eval $(call doit,$(task),$(tgt))))))

ifeq ($(OS),Windows_NT)
else
install : all
	mkdir -p $(PREFIX)/bin $(PREFIX)/libs
	for file in $(TARGETS); do cp $$file/$$file $(PREFIX)/bin; done
	rm -f $(PREFIX)/bin/ppmtoslr $(PREFIX)/bin/slrtoppm
	cd $(PREFIX)/bin && ln -s ppmtosl2 ppmtoslr
	cd $(PREFIX)/bin && ln -s sl2toppm slrtoppm
	cp libzxntools/libzxntools.a $(PREFIX)/libs
	-cp libzxntools/libzxntools.so $(PREFIX)/libs
endif

#include image.mk
#TARGETS=fonttotiles getpalette imagetoasm paltoasm paltoppm pbmtoshr	\
#	ppmtoscr ppmtoshc ppmtosl2 scrtoppm shctoppm shrtopbm		\
#	sl2toppm
#
#define all_t =
#all : all-$(1)
#all-$(1):
#	$(MAKE) -C $(1)
#endef
#
#$(foreach _, $(TARGETS) libzxntools, $(eval $(call all_t,$_)))
#
#.PHONY : $(TARGETS) libzxntools clean distclean install
#
#define clean_t =
#clean : clean-$(1)
#clean-$(1):
#	$(MAKE) -C $(1) clean
#endef
#
#$(foreach _, $(TARGETS) libzxntools, $(eval $(call clean_t,$_)))
#
#define distclean_t =
#distclean : clean-$(1) distclean-$(1)
#distclean-$(1):
#	$(MAKE) -C $(1) distclean
#endef
#
#$(foreach _, $(TARGETS) libzxntools, $(eval $(call distclean_t,$_)))
#
#ifeq ($(OS),Windows_NT)
#else
#install : all
#	mkdir -p $(PREFIX)/bin $(PREFIX)/libs
#	for file in $(TARGETS); do cp $$file/$$file $(PREFIX)/bin; done
#	rm -f $(PREFIX)/bin/ppmtoslr $(PREFIX)/bin/slrtoppm
#	ln -s $(PREFIX)/bin/ppmtosl2 $(PREFIX)/bin/ppmtoslr
#	ln -s $(PREFIX)/bin/sl2toppm $(PREFIX)/bin/slrtoppm
#	cp libzxntools/libzxntools.a $(PREFIX)/libs
#	-cp libzxntools/libzxntools.so $(PREFIX)/libs
#endif

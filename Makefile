TARGETS=image nexcreator zxother zxnftp
TASKS=all clean distclean install
PREFIX=$(CURDIR)

default: all

binary: install
	-rm $(PREFIX)/bin/zxnftp.conf
	cd $(PREFIX) && tar czf binary.tgz bin libs man

.PHONY: $(TASKS) binary

define doit
$(1): $(1)-$(2)
$(1)-$(2):
	$(MAKE) PREFIX=$(PREFIX) -C $(2) $(1)
endef

x := $(foreach task, $(TASKS), $(eval y = $(foreach tgt, $(TARGETS), $(eval $(call doit,$(task),$(tgt))))))

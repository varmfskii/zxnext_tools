TARGETS=image nexcreator zxnftp zxother
TASKS=all clean distclean install

PREFIX=$(CURDIR)

default: all
install: all
distclean: clean

.PHONY : $(TARGETS) $(TASKS)

define do_all =
$(1) : $(1)-$(2)
$(1)-$(2):
	$(MAKE) -C $(2) $(1)
endef

# iterate over tasks and targets
$(foreach task, $(TASKS), $(eval \
	$(foreach tgt, $(TARGETS), $(eval $(call do_all,$(task),$(tgt))))))


ifneq ($(IMAGE_MK),1)
include ../image.mk
endif
OBJS=fonttotiles.o
fonttotiles : $(OBJS)
	$(CC) -o $@ $^

fonttotiles.o : fonttotiles.c

.PHONY : clean distclean

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) fonttotiles

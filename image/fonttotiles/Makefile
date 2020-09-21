ifneq ($(IMAGE_MK),1)
include ../image.mk
endif
OBJS=fonttotiles.o

all: fonttotiles

fonttotiles : $(OBJS)
	$(CC) -o $@ $^

fonttotiles.o : fonttotiles.c

.PHONY : all clean distclean

clean :
	$(RM) $(OBJS)  *~

distclean : clean
	$(RM) fonttotiles

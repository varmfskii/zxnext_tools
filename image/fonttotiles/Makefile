CC=gcc
CFLAGS=-Wall
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS += -O3
endif
OBJS=fonttotiles.o
fonttotiles : $(OBJS)
	$(CC) -o $@ $^

fonttotiles.o : fonttotiles.c

.PHONY : clean distclean

clean :
	rm -f $(OBJS)  *~

distclean : clean
	rm -f fonttotiles

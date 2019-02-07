CC = gcc
CFLAGS = -O2 -Wall
OBJS=NexCreator.o addFile.o getBankOrder.o getHex.o getInt.o getNextBank.o \
	getRealBank.o getString.o skipSpace.o use8BitPalette.o

NexCreator : $(OBJS)
NexCreator.o : NexCreator.c NexCreator.h
addFile.o : addFile.c NexCreator.h
getBankOrder.o : getBankOrder.c NexCreator.h
getHex.o : getHex.c NexCreator.h
getInt.o : getInt.c NexCreator.h
getNextBank.o : getNextBank.c NexCreator.h
getRealBank.o : getRealBank.c NexCreator.h
getString.o : getString.c NexCreator.h
skipSpace.o : skipSpace.c NexCreator.h
use8BitPalette.o : use8BitPalette.c NexCreator.h

.PHONY : clean distclean

clean :
	rm -f $(OBJS) *~

distclean : clean
	rm -f NexCreator

CC = gcc
CFLAGS = -Wall -std=gnu99
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG -g
else
CFLAGS += -O3
endif
OBJS=nexcreator.o addFile.o cmdBANK.o cmdBMP.o cmdCOR.o cmdMMU.o cmdPCSP.o \
	cmdXSLR.o cmdSCR.o cmdSHC.o cmdSHR.o cmdXSL2.o cmdSLR.o cmddef.o \
	getBankOrder.o getHex.o getInt.o getNextBank.o getRealBank.o \
	getString.o getcommand.o skipSpace.o use8BitPalette.o

all: nexcreator
nexcreator : $(OBJS)
addFile.o : addFile.c nexcreator.h
cmdBANK.o : cmdBANK.c nexcreator.h
cmdBMP.o : cmdBMP.c nexcreator.h
cmdCOR.o : cmdCOR.c nexcreator.h
cmdMMU.o : cmdMMU.c nexcreator.h
cmdPCSP.o : cmdPCSP.c nexcreator.h
cmdSCR.o : cmdSCR.c nexcreator.h
cmdSHC.o : cmdSHC.c nexcreator.h
cmdSHR.o : cmdSHR.c nexcreator.h
cmdSLR.o : cmdSLR.c nexcreator.h
cmdXSL2.o : cmdXSL2.c nexcreator.h
cmdXSLR.o : cmdXSLR.c nexcreator.h
cmddef.o : cmddef.c nexcreator.h
getBankOrder.o : getBankOrder.c nexcreator.h
getHex.o : getHex.c nexcreator.h
getInt.o : getInt.c nexcreator.h
getNextBank.o : getNextBank.c nexcreator.h
getRealBank.o : getRealBank.c nexcreator.h
getString.o : getString.c nexcreator.h
getcommand.o : getcommand.c nexcreator.h
nexcreator.o : nexcreator.c nexcreator.h
parseCSV.o : parseCSV.c nexcreator.h
readline.o : readline.c nexcreator.h
skipSpace.o : skipSpace.c nexcreator.h
use8BitPalette.o : use8BitPalette.c nexcreator.h

.PHONY : install clean distclean

install : nexcreator
	cp nexcreator ../bin

clean :
	rm -f $(OBJS) *~

distclean : clean
	rm -f nexcreator

install: all
	cp nexcreator $(PREFIX)/bin/

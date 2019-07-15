OBJS=asm.o asmfile.o cpc.o main.o pasmo.o pasmotypes.o \
	spectrum.o tap.o token.o trace.o tzx.o
CXX=g++
CXXFLAGS=-O3

all : pasmo

pasmo : $(OBJS)
	$(CXX) -o $@ $^

asm.o : asm.cpp asm.h token.h asmfile.h cpc.h tap.h tzx.h spectrum.h trace.h
asmfile.o : asmfile.cpp asmfile.h
cpc.o : cpc.cpp cpc.h
main.o : main.cpp pasmo.h
pasmo.o : pasmo.cpp pasmo.h asm.h
pasmotypes.o : pasmotypes.cpp pasmotypes.h
spectrum.o : spectrum.cpp spectrum.h
tap.o : tap.cpp tap.h
token.o : token.cpp token.h
tzx.o : tzx.cpp tzx.h pasmotypes.h

.PHONY : clean distclean

clean :
	rm -f $(OBJS) *~

distclean : clean
	rm -f pasmo

install: all
	cp pasmo $(PREFIX)/bin/

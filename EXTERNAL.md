Some notes on other tools for software development for the ZX Spectrum
next on the Pi accelerator.

* pasmo: git located at https://github.com/spec-chum/pasmo.git

This the git is set up for compilation on Windows, but the only thing
needed for easy compilation under Linux including Raspbian is a
Makefile which can be found in the pasmoNext directory.

* sjasmplus: git located at https://github.com/z00m128/sjasmplus.git

This git is set up for compilation under Linux, but currently (as of 2
July 2019) there is an assumption that size_t and unsigned long are
equivalent which causes and error on line 89 of sjasm/io_tdr.cpp when
compiling under Raspbian. If you change 8UL on this line to (size_t)
8UL it will then compile.

* z88dk: git located at https://github.com/z88dk/z88dk.git

This will compile under Raspbian provided you have enough memory
(without swap the 512k on the lower end models is not
sufficient).

* zesaurx: git located at https://github.com/chernandezba/zesarux.git

This git is set up for Raspbian, but the lower powered models of the
Pi have poor performance when running the emulator. Two things can be
done to mitigate this: configure and compile with CFLAGS=-O3 and
overclock the Pi in question.

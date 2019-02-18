# ZX Spectrum Next tools

See LICENSE.md for license

See PHILOSOPHY.md for philosophy statement

See TODO.md for things to do

## Tools for ZX Spectrum Next

- getpalette
- imagetoasm
- hicoltoppm
- hirestopbm
- layer2toppm
- lorestoppm
- nexcreator
- paltoasm
- ppmtohicol
- ppmtolayer2
- ppmtolores
- ppmtoula
- ulatoppm
- libzxntools library
	
## General Usage

&lt;command&gl; [&lt;options&gt;]  [&lt;infile&gt;]  [&lt;outfile&gt;]

## Common Options

- -h --help    show thie help message
- -i --in      set input file (stdin)
- -o --out     set output file (stdout)
- -V --version get version information
- -v --verbose increase verbosity
	
The input file will be one of:

1. file specified by --in
2. first unused command line option
3. standard input

The output file will be one of:

1. file specified by --out
2. first unused command line option if none have been used by input file
3. second unused command line option
4. standard output

## Binaries

Binaries are currently provided for Raspbian and Ubuntu x86-64 which
should work on any Linux distro that has the appropriate version of
libnetpbm and can handle the appropriate architecture armhf (armv6) or
x86-64.

## Building

1. Install libnetpbm for your platorm
2. check if pam.h is located in a directory in your include path (/usr/linclude/pam.h) , or in the netpbm direcotry in your include path (/usr/include/netpbm/pam.h)
3. if in your path "make", if in subdirectory "make PREFIX=1"

## Suggestions etc.

Suggestions, complaints, and error reports to varmfskii at gmail dot com


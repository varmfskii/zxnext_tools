# Image tools for converting files to and from ZX Spectrum Next file

A set of tools used to complement the netpbm set of image processing
tools with reasonable interoperability with the functions provided by
imagemagick and graphicsmagick.

The tools use a fairly unified set of options to make understanding
them easier and all have builtin help functionality. The expectation
is for the user to process their images with other tools and perform
final conversion from ppm (occasionally pbm) to ZX Spectrum Next
formats using these tools.

Ideally an image passed to these tools will already be using the
Next's 3:3:3 colourspace, already have the correct number of colours,
and already be the right resolution. When this is not true the tools
don't fail, but may not do what you wish.

PPM is not an indexed image format. This is a potential problem when
dealing with a system like the ZX Next that uses indexed colour. The
solution here is that, where indexed colour is necessary, the tools
support the use of a separate palette file and when not passed a
palette file use the default palette of the ZX Spectrum Next.

## Image Tools for ZX Spectrum Next

- fonttotiles - convert 768 byte font files to ZX Spectrum Next tiles
- getpalette - extract palette information from an image
- imagetoasm - convert an image to assembly language source for ZX Next sprites or tiles
- libzxntools library - support functions for tools
- paltoasm - convert a palette file to assembly source code
- paltoppm - convert a palette file to ppm
- pbmtoshr - convert a pbm file to a Timex hi-resolution screen dump
- ppmtoscr - convert a ppm file to a ZX Spectrum screen dump
- ppmtoshc - convert a ppm file to a Times hi-colour screen dump
- ppmtosl2 - convert a ppm file to a ZX Next layer2 screen dump
- ppmtoslr - convert a ppm file to a ZX Next lo-resolution screen dump
- scrtoppm - convert a ZX Spectrum screen dump to a ppm file
- shctoppm - convert a Timex hi-colour screen dump to a ppm file 
- shrtopbm - convert a Timex hi-resolution screen dump to a pbm file
- sl2toppm - convert a ZX Next layer2 screen dump to a ppm file
- slrtoppm - convert a ZX Next lo-resolution screen dump to a ppm file

## General Usage

&lt;command&gt; [&lt;options&gt;]  [&lt;infile&gt;]  [&lt;outfile&gt;]

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
2. check if pam.h is located in a directory in your include path (/usr/linclude/pam.h) , or in the netpbm directory in your include path (/usr/include/netpbm/pam.h)
3. if in your path "make", if in subdirectory "PAMPREFIX=1 make"

## Suggestions etc.

Suggestions, complaints, and error reports to varmfskii at gmail dot com


ZX Spectrum Next tools: See LICENSE.md for license

Tools for ZX Spectrum Next:

	- getpalette
	- imagetoasm
    - layer2toppm
	- lorestoppm
	- nexcreator
    - paltoasm
    - ppmtolayer2
	- ppmtolores
    - libzxntools library
	
In general command format will be:

&lt;command&gl; [&lt;options&gt;]  [&lt;infile&gt;]  [&lt;outfile&gt;]

common options:

	-h --help    show thie help message
	-i --in      set input file (stdin)
	-o --out     set output file (stdout)
    -V --version get version information
	-v --verbose increase verbosity
	
The input file will be one of:

	1) file specified by --in
	2) first unused command line option
	3) standard input
	
The output file will be one of:

	1) file specified by --out
	2) first unused command line option if none have been used by input file
	3) second unused command line option
	4) standard output
	
A note on programming philosophy and image formats.  These utilities
are written in the tradition of having programs that do one thing and
(try to) do it well. For this reason the idea is to have a lot of
small programs rather than a few big ones that can do everything. As
to image formats, there are a lot of image formats they have their
strengths and weaknesses. Since I have access to things like
ImageMagick and netpbm+, I see little reason to support a lot of image
formats directly. The choices I have made are pbm, pgm, and ppm (tying
directly to the ideas of netpbm+ which uses these formats as
intermediate formats). As a result most require the presence of
libnetpbm to compile/run.

Suggestions, complaints, and error reports to varmfskii at gmail dot com

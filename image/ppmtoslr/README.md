# ppmtoslr version 1.02.00 20190221

ppmtoslr: convert a ppm file to a lores image for the ZX Spectrum Next
(.SLR). If input image is not 128x96 uses the upper left corner of the
image (padding out as necessary).

## Usage: ppmtoslr [&lt;options&gt;]  [&lt;infile&gt;]  [&lt;outfile&gt;]

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
	
Requires libnetpbm

# getpalette version 1.01.01 20190215

getpalette: extract a raw binary palette from a ppm file

## Usage: getpalette [&lt;options&gt;]  [&lt;infile&gt;]  [&lt;outfile&gt;]

- -b --bits    set bit depth of palette (8)
- -h --help    show this help message
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

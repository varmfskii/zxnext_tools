# fonttotiles version 1.00.00 20190917

fonttofiles: convert 768 byte, 1 bit per pixel font files such as
included with z88dk to raw tilemaps for the ZX Spectrum Next


## Usage: fonttotiles [&lt;options&gt;]  [&lt;infile&gt;]  [&lt;outfile&gt;]

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

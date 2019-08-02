# imagetoasm version 1.01.01 20190215

imagettoasm: A tool for generating assembly source code for ppm images. It
takes a full image and splits it up into individual sprite or tile
sized sections.

## Usage: imagetoasm [&lt;options&gt;]  [&lt;infile&gt;]  [&lt;outfile&gt;]

options with defaults in parenthesis:

- -a	--asm		output assembly code (asm)
- -b	--bits		number of bits per pixel (8)
- -h	--help		show this help message
- -i	--in		input file (stdin)
- -l	--label		label in assembly file (label)
- -o	--out		output file (stdout)
- -O	--offset	offset (x and y) in image (0)
- -p	--pal		palette file (internal)
- -r	--raw		out raw binary data (asm)
- -s	--sprite	generate sprites = -b8 -z16
- -S	--skip		use ever nth pixel (1)
- -t	--tile		generate tiles = -b4 -z8
- -V    --version   get version information
- -v    --verbose increase verbosity
- -z	--size		element size (16)

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

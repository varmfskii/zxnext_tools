img2asm: A tool for generating assembly source code for ppm images. It
takes a full image and splits it up into individual sprite or tile
sized sections.

Usage: img2asm <options>

options with defaults in parenthesis:

	-a	--asm		output assembly code (asm)
	-b	--bits		number of bits per pixel (8)
	-h	--help		show this help message
	-i	--in		input file (stdin)
	-l	--label		label in assembly file (label)
	-o	--out		output file (stdout)
	-O	--offset	offset (x and y) in image (0)
	-p	--pal		palette file (internal)
	-r	--raw		out raw binary data (asm)
	-s	--sprite	generate sprites = -b8 -z16
	-S	--skip		use ever nth pixel (1)
	-t	--tile		generate tiles = -b4 -z8
	-z	--size		element size (16)

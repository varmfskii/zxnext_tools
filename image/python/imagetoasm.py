#!/usr/bin/env python3
import getopt
import sys

from PIL import Image

import zxntools as zxn

BITS = 8
LABEL = "label"
OFFSET = 0
SKIP = 1
SIZE = 16
RAW = 0
ASM = 1
PGM = 2
VERSION = "1.00.00"
DATE = "20210324"


def my_help(name):
    version()
    sys.stderr.write(
        """Usage: {} [<options>] [<infile>] [<outfile>]
\toptions are
\t-a\t--asm\t\toutput assembly code (asm)
\t-b\t--bits\t\tset bit depth of palette ({})
\t-h\t--help\t\tshow this help message
\t-i\t--in\t\tinput file (stdin)
\t-l\t--label\t\tlabel in assembly file({})
\t-o\t--out\t\toutput file (stdout)
\t-O\t--offset\toffset (x and y) in image ({})
\t-p\t--pal\t\tpalette file (internal)
\t-r\t--raw\t\toutput raw binary data (asm)
\t-s\t--sprite\tgenerate sprites = -b8 -z16
\t-S\t--skip\t\tuse every nth pixel ({})
\t-V\t--version\tget version information
\t-v\t--verbose\tincrease verbosity
\t-z\t--size\t\telement size ({})
""".format(name, BITS, LABEL, OFFSET, SKIP, SIZE))


def version():
    sys.stderr.write("imagetoasm version {} {}\n".format(VERSION, DATE))
    zxn.version(True)


def decimate(img, offx, offy, skipx, skipy):
    inx, iny = img.size
    outx = (inx - offx + skipx - 1) // skipx
    outy = (iny - offy + skipy - 1) // skipy
    rv = Image.new('RGB', (outx, outy))

    y2 = offy
    for y1 in range(outy):
        x2 = offx
        for x1 in range(outx):
            rv.putpixel((x1, y1), img.getpixel((x2, y2)))
            x2 += skipx
        y2 += skipy

    return rv


def writeraw(fd, img, bits, txsz, tysz):
    ixsz, iysz = img.size
    tx = ixsz // txsz
    ty = iysz // tysz
    mask = (1 << bits) - 1
    buf = []
    for tr in range(ty):
        rbase = tr * tysz
        for tc in range(tx):
            cbase = tc * txsz
            for r in range(tysz):
                for c in range(0, txsz, 8 // bits):
                    v = 0
                    for b in range(8 // bits):
                        v = (v << bits) | img.getpixel((c + cbase + b, r + rbase)) & mask
                    buf.append(v)

    fd.write(bytes(buf))


def writepgm(fd, img, bits, txsz, tysz):
    ixsz, iysz = img.size
    tx = ixsz // txsz
    ty = iysz // tysz
    mask = (1 << bits) - 1
    fd.write(bytes("P5\n{} {}\n{}\n".format(txsz, ixsz * tx, mask), 'ascii'))
    buf = []
    for tr in range(ty):
        rbase = tr * tysz
        for tc in range(tx):
            cbase = tc * txsz
            for r in range(tysz):
                for c in range(0, txsz, 8 // bits):
                    for b in range(8 // bits):
                        buf.append(img.getpixel((c + cbase + b, r + rbase)) & mask)

    fd.write(bytes(buf))


def writeasm(fd, img, bits, label, txsz, tysz):
    ixsz, iysz = img.size
    tx = ixsz // txsz
    ty = iysz // tysz
    mask = (1 << bits) - 1

    fd.write("{}\n".format(label))
    cnt = 0
    col = 0

    for tr in range(ty):
        rbase = tr * tysz

        for tc in range(tx):
            cbase = tc * txsz
            if col != 0:
                fd.write("\n")
                col = 0
            fd.write(";; {} {:02x}\n".format(label, cnt))
            cnt += 1
            for r in range(tysz):
                for c in range(0, txsz, 8 // bits):
                    v = 0
                    for b in range(8 // bits):
                        v = (v << bits) | img.getpixel((c + cbase + b, r + rbase)) & mask
                    if col == 0:
                        fd.write("\tdefb {:02x}".format(v))
                    elif col != 15:
                        fd.write(", {:02x}".format(v))
                    else:
                        fd.write(", {:02x}\n".format(v))
                    col = (col + 1) % 16

    if col != 0:
        fd.write("\n")
    fd.write("{}_end:\n".format(label))


verbose = 0
offset = OFFSET
skip = SKIP
size = SIZE
bits = BITS
outtype = ASM
label = LABEL
inname = None
outname = None
palname = None
palfile = None

opts = "ab:ghi:l:o:O:p:rsS:tvVz:"
longopts = ['asm', 'bits=', 'pgm', 'help', 'in=', 'label=', 'out=', 'offset=',
            'pal=', 'raw', 'sprite', 'skip=', 'tile' 'version' 'verbose', 'size=']

try:
    optlist, arglist = getopt.getopt(sys.argv[1:], opts, longopts)
except getopt.GetoptError as err:
    sys.stderr.write("{}\n".format(err))
    exit(1)

for opt, arg in optlist:
    if opt in ('-b', '--bits'):
        bits = int(arg)
        if bits != 1 and bits != 2 and bits != 4 and bits != 8:
            sys.stderr.write("Unsupported bit depth: {}\n".format(bits))
            exit(1)

    elif opt in ('-g', '--pgm'):
        outtype = PGM

    elif opt in ('-h', '--help'):
        my_help(sys.argv[0])
        exit(0)

    elif opt in ('-i', '--in'):
        inname = arg

    elif opt in ('-l', '--label'):
        label = arg

    elif opt in ('-O', '--offset'):
        offset = int(arg)

    elif opt in ('-o', '--out'):
        outname = arg

    elif opt in ('-p', '--pal'):
        palname = arg

    elif opt in ('-r', '--raw'):
        outtype = RAW

    elif opt in ('-s', '--sprite'):
        bits = 8
        size = 16

    elif opt in ('-S', '--skip'):
        skip = int(arg)

    elif opt in ('-t', '--tile'):
        bits = 4
        size = 8

    elif opt in ('-V', '--version'):
        version()
        exit(0)

    elif opt in ('-v', '--verbose'):
        verbose += 1

    elif opt in ('-z', '--size'):
        size = int(arg)

    else:
        sys.stderr.write("Illegal option {}\n", opt)
        exit(1)

if palname is not None:
    try:
        palfile = open(palname, 'rb')
    except OSError:
        sys.stderr.write("Unable to open {}\n".format(inname))
        exit(1)

if len(arglist) > 0 and inname is None:
    inname = arglist.pop(0)

if len(arglist) > 0 and outname is None:
    outname = arglist.pop(0)

if inname is None:
    sys.stderr.write("No input file\n")

if outname is None:
    sys.stderr.write("No output file\n")

try:
    infile = open(inname, 'rb')
except OSError:
    sys.stderr.write("Unable to open {}\n".format(inname))
    exit(1)

try:
    if outtype == RAW or outtype == PGM:
        outfile = open(outname, 'wb')
    else:
        outfile = open(outname, 'w')
except OSError:
    sys.stderr.write("Unable to open {}\n".format(outname))
    exit(1)

zxn.setverbose(verbose)
image = Image.open(infile)
image.convert('RGB')
# rgb = image.data()

if palfile is not None:
    pal = zxn.readpal(palfile)
else:
    pal = zxn.makepal(zxn.palette(bits))

dec = decimate(image, offset, offset, skip, skip)
dec = dec.quantize(colors=(1 << bits), palette=pal, dither=Image.NONE)

xsz, ysz = dec.size
if xsz % size != 0 or ysz % size != 0:
    sys.stderr.write("Not perfectly tilable\n")
    exit(-1)

if outtype == RAW:
    writeraw(outfile, dec, bits, size, size)
elif outtype == ASM:
    writeasm(outfile, dec, bits, label, size, size)
elif outtype == PGM:
    writepgm(outfile, dec, bits, size, size)
else:
    sys.stderr.write("Output type error\n")

infile.close()
outfile.close()

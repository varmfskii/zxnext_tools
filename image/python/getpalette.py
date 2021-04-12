#!/usr/bin/env python3
import getopt
import sys
from PIL import Image
import zxntools as zxn

VERSION = "1.00.00"
DATE = "20210324"
BITS = 8


def my_help(name):
    version()
    sys.stderr.write(("Usage: {} [<options>] [<infile>] [<outfile>]\n"
                      "	options are\n"
                      "	-b	--bits		set bit depth of palette ({})\n"
                      "	-h	--help		show this help message\n"
                      "	-i	--in		input file (stdin)\n"
                      "	-o	--out		output file (stdout)\n"
                      "	-V	--version	get version information\n"
                      "	-v	--verbose	increase verbosity\n").format(name, bits))


def version():
    sys.stderr.write("getpalette version {} {}\n".format(VERSION, DATE))
    zxn.version(True)


def rgb2pal(rgb, pal_len):
    col_order = [0] * 512
    colors = []

    for i in range(512):
        colors.append([0, i])

    num_col = 0

    for pixel in rgb:
        r = zxn.pal8to3(pixel[0])
        g = zxn.pal8to3(pixel[1])
        b = zxn.pal8to3(pixel[2])
        color = (r << 6) | (g << 3) | b
        if colors[color][0] == 0:
            col_order[num_col] = color
            num_col += 1
        colors[color][0] += 1

    pal = []
    if num_col <= pal_len:
        for i in range(pal_len):
            color = colors[col_order[i % num_col]][1]
            r = zxn.pal3to8((color >> 6) & 7)
            g = zxn.pal3to8((color >> 3) & 7)
            b = zxn.pal3to8(color & 7)
            a = 0xff
            pal.append([r, b, g, a])

    else:
        colors.sort(reverse=True)
        for i in range(len):
            color = colors[i][1]
            r = zxn.pal3to8((color >> 6) & 7)
            g = zxn.pal3to8((color >> 3) & 7)
            b = zxn.pal3to8(color & 7)
            a = 0xff
            pal.append([r, b, g, a])

    return pal


bits = BITS
infile = sys.stdin
outfile = sys.stdout
verbose = 0

opts = "b:hi:o:Vv"
longopts = ['bits=', 'help', 'in=', 'out=', 'version' 'verbose']

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

    elif opt in ('-h', '--help'):
        my_help(sys.argv[0])
        exit(0)

    elif opt in ('-i', '--in'):
        try:
            infile = open(arg, 'rb')
        except OSError:
            sys.stderr.write("Unable to open {}\n".format(arg))
            exit(1)

    elif opt in ('-o', '--out'):
        try:
            outfile = open(arg, 'wb')
        except OSError:
            sys.stderr.write("Unable to open {}\n".format(arg))
            exit(1)

    elif opt in ('-V', '--version'):
        version()
        exit(0)

    elif opt in ('-v', '--verbose'):
        verbose += 1

    else:
        sys.stderr.write("Illegal option {}\n", opt)
        exit(1)

if len(arglist) > 0 and infile == sys.stdin:
    try:
        infile = open(arglist[0], 'rb')
    except OSError:
        sys.stderr.write("Unable to open {}\n".format(arglist[0]))
        exit(1)

    arglist.pop(0)

if len(arglist) > 0 and outfile == sys.stdout:
    try:
        outfile = open(arglist[0], 'wb')
    except OSError:
        sys.stderr.write("Unable to open {}\n".format(arglist[0]))
        exit(1)

    arglist.pop(0)

image = Image.open(infile)
image.convert('RGB')
rgb = image.getdata()
pal = rgb2pal(rgb, 1 << bits)

for color in pal:
    outfile.write(bytes(color))

infile.close()
outfile.close()

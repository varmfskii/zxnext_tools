#!/usr/bin/env python3
import getopt
import sys
import zxntools as zxn

VERSION = "1.00.00"
DATE = "20210324"
BITS = 8
LABEL = 'label'


def my_help(name):
    version()
    sys.stderr.write(
        ("Usage: {} [<options>] [<infile>] [<outfile>]\n"
         "	options are\n"
         "	-b	--bits		set bit depth of palette ({})\n"
         "	-h	--help		show this help message\n"
         "	-i	--in		input file (stdin)\n"
         "	-l	--label		set label for assembly file ({})\n"
         "	-o	--out		output file (stdout)\n"
         "	-V	--version	get version information\n"
         "	-v	--verbose	increase verbosity\n").format(name, bits, LABEL))


def version():
    sys.stderr.write("paltoasm version {} {}\n".format(VERSION, DATE))
    zxn.version(True)


def writeasm(pal, outfile, label, colors):
    palette = pal.getpalette()

    outfile.write("{}:\n".format(label))

    for i in range(colors):
        v = (palette.pop(0) * 14 + 1) // 510
        v = (v << 3) | (palette.pop(0) * 14 + 1) // 510
        v = (v << 3) | (palette.pop(0) * 14 + 1) // 510
        if i % 8 == 0:
            outfile.write("\tdefb ${:02x}, ${:02x}".format(v >> 1, v & 1))
        elif i % 8 == 7:
            outfile.write(", ${:02x}, ${:02x}\n".format(v >> 1, v & 1))
        else:
            outfile.write(", ${:02x}, ${:02x}".format(v >> 1, v & 1))

    if i % 8 != 0:
        outfile.write("\n")

    outfile.write("{}_end:\n".format(label))


bits = BITS
verbose = 0
inname = None
outname = None
label = LABEL

opts = "b:hi:l:o:Vv"
longopts = ['bits=', 'help', 'in=', 'label=', 'out=', 'version' 'verbose']

try:
    optlist, arglist = getopt.getopt(sys.argv[1:], opts, longopts)
except getopt.GetoptError as err:
    sys.stderr.write("{}\n".format(err))
    exit(1)

for opt, arg in optlist:
    if opt in ('-b', '--bits'):
        if bits != 1 and bits != 2 and bits != 4 and bits != 8:
            sys.stderr.write("Unsupported bit depth: {}\n".format(bits))
            exit(1)
        bits = int(arg)

    elif opt in ('-h', '--help'):
        my_help(sys.argv[0])
        exit(0)

    elif opt in ('-i', '--in'):
        inname = arg

    elif opt in ('-l', '--label'):
        label = arg

    elif opt in ('-o', '--out'):
        outname = arg

    elif opt in ('-V', '--version'):
        version()
        exit(0)

    elif opt in ('-v', '--verbose'):
        verbose += 1

    else:
        sys.stderr.write("Illegal option {}\n", opt)
        exit(1)

if len(arglist) > 0 and inname is None:
    inname = arglist.pop(0)

if len(arglist) > 0 and outname is None:
    outname = arglist.pop(0)

if inname is None:
    sys.stderr.write("No input file\n")
    exit(1)

try:
    infile = open(inname, 'rb')
except:
    sys.stderr.write("Unable to open {}\n".format(inname))
    exit(1)

if outname is None:
    outfile = sys.stdout
else:
    try:
        outfile = open(outname, 'w')
    except:
        sys.stderr.write("Unable to open {}\n".format(outname))
        exit(1)

zxn.setverbose(verbose)
print(verbose)
pal = zxn.readpal(infile)
writeasm(pal, outfile, label, 1 << bits)
infile.close()
outfile.close()

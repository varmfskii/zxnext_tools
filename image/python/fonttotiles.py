#!/usr/bin/env python3
import getopt
import sys
import zxntools as zxn

VERSION = "1.00.00"
DATE = "20210324"
INK = 15
PAPER = 0


def my_help(name):
    version()
    sys.stderr.write(
        ("Usage: {} [<options>] [<infile>] [<outfile>]\n"
         "	options are\n"
         "	-b	--bg		set paper color ({})\n"
         "	-f	--fg		set ink color ({})\n"
         "	-h	--help		print this help message\n"
         "	-I	--ink		set ink color ({})\n"
         "	-i	--in		input file (stdin)\n"
         "	-o	--out		output file (stdout)\n"
         "	-P	--paper		set paper color ({})\n"
         "	-V	--version	get version information\n"
         "	-v	--verbose	increase verbosity\n").format(name, paper, ink, ink, paper))


def version():
    sys.stderr.write("fonttotiles version {} {}\n".format(VERSION, DATE))
    zxn.version(True)


ink = INK
paper = PAPER
infile = sys.stdin
outfile = sys.stdout

opts = "b:f:hI:i:o:P:Vv"
longopts = ['bg=', 'fg=', 'help', 'ink=', 'in=', 'out=', 'paper=', 'version' 'verbose']

try:
    optlist, arglist = getopt.getopt(sys.argv[1:], opts, longopts)
except getopt.GetoptError as err:
    sys.stderr.write("{}\n".format(err))
    exit(1)
verbose = 0

for opt, arg in optlist:
    if opt in ('-b', '-bg', '-P', '--paper'):
        paper = int(arg)
        if paper < 0 or paper > 15:
            sys.stderr.write("Illegal paper value: {}\n".format(arg))
            exit(1)

    elif opt in ('-f', '--fg', '-I', '--ink'):
        ink = int(arg)
        if ink < 0 or ink > 15:
            sys.stderr.write("Illegal ink value: {}\n".format(arg))
            exit(1)

    elif opt in ('-h', '--help'):
        my_help(sys.argv[0])
        exit(0)

    elif opt in ('-i', '--in'):
        try:
            infile = open(arg, 'rb')
        except (OSError, IOError) as e:
            sys.stderr.write("Unable to open {} - {}\n".format(arg, e))
            exit(1)

    elif opt in ('-o', '--out'):
        try:
            outfile = open(arg, 'wb')
        except (OSError, IOError) as e:
            sys.stderr.write("Unable to open {} - {}\n".format(arg, e))
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
    except (OSError, IOError) as e:
        sys.stderr.write("Unable to open {} - {}\n".format(arglist[0], e))
        exit(1)

    arglist.pop(0)

if len(arglist) > 0 and outfile == sys.stdout:
    try:
        outfile = open(arglist[0], 'wb')
    except (OSError, IOError) as e:
        sys.stderr.write("Unable to open {} - {}\n".format(arglist[0], e))
        exit(1)

    arglist.pop(0)

for i in range(32 * 8 * 4):
    outfile.write(b'\0')

indata = infile.read()
outdata = []
for c in indata:
    for i in range(4):
        if c & 0x80 != 0:
            v = ink << 4
        else:
            v = paper << 4
        if c & 0x40 != 0:
            v |= ink
        else:
            v |= paper
        c = c << 2
        outdata.append(v)

outfile.write(bytes(outdata))
infile.close()
outfile.close()

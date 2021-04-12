#!/usr/bin/env python3
import getopt
import sys
import struct
from PIL import Image
import zxntools as zxn

VERSION = "1.00.00"
DATE = "20210324"
BITS = 8
FORMAT = None
NAME = 'paltoimg'

def help(name):
    version()
    sys.stderr.write(
"""Usage: {} [<options>] [<infile>] [<outfile>]
	options are
	-b	--bits		set bit depth of palette ({})
	-f	--format	set output file format ({})
	-h	--help		show this help message
	-i	--in		input file (stdin)
	-o	--out		output file (stdout)
	-V	--version	get version information
	-v	--verbose	increase verbosity
""".format(name, FORMAT, BITS))

    
def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)

    
bits = BITS
verbose = 0
inname = None
outname = None
outfmt = FORMAT

opts = "b:f:hi:o:Vv"
longopts=['bits=', 'format=', 'help', 'in=', 'out=', 'version' 'verbose']

try:
    optlist, arglist = getopt.getopt(sys.argv[1:], opts, longopts)
except getopt.GetoptError as err:
    sys.stderr.write("{}\n".format(err))
    exit(1)

for opt, arg in optlist:
    if opt in ('-b', '--bits'):
        if bits != 1 and bits != 2 and bits != 4 and bits !=8:
            sys.stderr.write("Unsupported bit depth: {}\n".format(bits))
            exit(1)
        bits = int(arg)

    elif opt in ('-f', '--format'):
        outfmt = arg.upper()

    elif opt in ('-h', '--help'):
        help(sys.argv[0])
        exit(0)

    elif opt in ('-i', '--in'):
        inname = arg

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

if len(arglist)>0 and inname==None:
    inname = arglist.pop(0)

if len(arglist)>0 and outname==None:
    outname = arglist.pop(0)

if inname==None:
    sys.stderr.write("No input file\n")
    exit(1)
    
try:
    infile=open(inname, 'rb')
except:
    sys.stderr.write("Unable to open {}\n".format(inname))
    exit(1)
        
if outname==None:
    outfile = sys.stdout
    if outfmt==None:
        outfmt='PPM'
        
else:
    try:
        outfile=open(outname, 'wb')
    except:
        sys.stderr.write("Unable to open {}\n".format(outname))
        exit(1)

zxn.setverbose(verbose)
pal = zxn.readpal(infile)

try:
    pal.save(outfile, format=outfmt) 
except:
    try:
        pal.convert('RGB').save(outfile, format=outfmt)
    except:
        pal.convert('RGB').save(outfile, format='PPM')
        
infile.close()
outfile.close()

#!/usr/bin/env python3
import sys

import scrtoimg as scr
import shrtoimg as shr
import sl2toimg as sl2
import zxntools as zxn

VERSION = "1.00.00"
DATE = "20210407"
NAME = 'zxnexttoimg'


def my_help(name):
    version()
    sys.stderr.write(
        ("Usage: {} [<options>] [<infile>] [<outfile>]\n"
         "\tgeneral options are\n"
         "\t-3\t--320\t\tPrefer 320x192x256 resoultion\n"
         "\t-6\t--640\t\tPrefer 640x192x16 resoultion\n"
         "\t-h\t--help\t\tshow this help message\n"
         "\t-i\t--in\t\tinput file (stdin)\n"
         "\t-o\t--out\t\toutput file (stdout)\n"
         "\t-p\t--pal\t\tpalette file (None)\n"
         "\t-V\t--version\tget version information\n"
         "\t-v\t--verbose\tincrease verbosity\n"
         "\t\t--scr\t\tZX Spectrum screen dump\n"
         "\t\t--shc\t\tTimex hi-color screen dump\n"
         "\t\t--shr\t\tTimex hi-resolution screen dump\n"
         "\t\t--sl2\t\tZX Next Layer 2 screen dump\n"
         "\t\t--slr\t\tZX Next lo-resoulution screen dump\n"
         ).format(name))


def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)


DEFAULTS = {
    'to_zxnext': False,
    'opts': "36hi:o:p:Vv",
    'long_opts': ['320', '320x256', '640', '640x256', 'help', 'in=', 'out=', 'pal=', 'version', 'verbose',
                  'mc', 'mlt', 'nxi', 'scr', 'shc', 'shr', 'sl2', 'slr'],
    'inks': 16,
    'papers': 16,
    'pal_type': zxn.Options.ULA,
    'num_colors': 0,
    'tile_y': 8,
    'res': (0, 0),
    'zxn_fmt': zxn.Options.AUTO,
    'help': my_help
}

if __name__ == "__main__":
    options = zxn.Options(sys.argv, DEFAULTS)
    img = None

    if options.zxn_fmt in (options.MC, options.MLT, options.SCR, options.SHC):
        img = scr.scrtoimg(options)
    elif options.zxn_fmt == options.SHR:
        img = shr.shrtoimg(options)
    elif options.zxn_fmt in (options.NXI, options.SL2, options.SLR):
        img = sl2.sl2toimg(options)
    else:
        sys.stderr.write("Unimplemented format\n")
        exit(0)

    if options.verbose > 1:
        img.resize((1024, 768)).show()
    try:
        img.save(options.outfile)
    except OSError:
        img.convert('RGB').save(options.outfile)

    options.outfile.close()

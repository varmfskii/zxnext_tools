#!/usr/bin/env python3
from PIL import Image
import numpy as np
import zxntools as zxn
import sys

NAME = 'shrtoimg'
VERSION = '1.00.00'
DATE = "11 Apr 2021"


def my_help(name):
    version()
    sys.stderr.write(
        ("Usage: {} [<options>] [<infile>] [<outfile>]\n"
         "\toptions are\n"
         "\t-D\t--double\tdouble vertical size\n"
         "\t-h\t--help\t\tshow this help message\n"
         "\t-i\t--in\t\tinput file (stdin)\n"
         "\t-o\t--out\t\toutput file (stdout)\n"
         "\t-V\t--version\tget version information\n"
         "\t-v\t--verbose\tincrease verbosity\n"
         ).format(name))


def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)


DEFAULTS = {
    'help': my_help,
    'inks': None,
    'long_opts': ['double', 'help', 'in=', 'out=', 'version', 'verbose'],
    'num_colors': None,
    'opts': 'Dhi:o:vV',
    'pal_type': None,
    'papers': None,
    'res': (512, 192),
    'tile_y': None,
    'to_zxnext': False,
    'zxn_fmt': zxn.Options.SHR
}


def shrtoimg(options):
    data_all = np.asarray(list(options.infile.read()))
    data = data_all[:12288].reshape((2, 3, 8, 8, 32))
    pixels = np.empty((192, 32, 2, 8))

    for pg in range(2):
        for r in range(192):
            r1 = r // 64
            r2 = (r // 8) & 7
            r3 = r & 7
            for b in range(8):
                pixels[r, :, pg, b] = data[pg, r1, r3, r2] & (128 >> b) == 0

    img = Image.new('1', (512, 192))
    img.putdata(list(pixels.reshape((98304,))))

    if options.double:
        img = img.resize((512, 384))

    return img


if __name__ == "__main__":
    options = zxn.Options(sys.argv, DEFAULTS)

    if options.verbose > 0:
        options.print()

    img = shrtoimg(options)

    if options.verbose > 1:
        img.resize((1024, 768)).show()

    img.save(options.outfile)

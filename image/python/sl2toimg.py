#!/usr/bin/env python3
import sys

import numpy as np
from PIL import Image

import zxntools as zxn

NAME = 'sl2toimg'
VERSION = '1.00.00'
DATE = "10 Apr 2021"


def my_help(name):
    version()
    sys.stderr.write(
        ("Usage: {} [<options>] [<infile>] [<outfile>]\n"
         "\toptions are\n"
         "\t-3\t--320x256\t320x192 prefer resoultion\n"
         "\t-6\t--640x256\t640x192 prefer resoultion\n"
         "\t-h\t--help\t\tshow this help message\n"
         "\t-i\t--in\t\tinput file (stdin)\n"
         "\t-o\t--out\t\toutput file (stdout)\n"
         "\t-p\t--pal\t\tpalette (none)"
         "\t-V\t--version\tget version information\n"
         "\t-v\t--verbose\tincrease verbosity\n"
         ).format(name))


def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)


DEFAULTS = {
    'help': my_help,
    'inks': None,
    'long_opts': ['320', '320x256', '640', '640x256', 'help', 'in=', 'out=', 'pal=', 'version', 'verbose'],
    'num_colors': None,
    'opts': '36hi:o:p:vV',
    'pal_type': None,
    'papers': None,
    'res': (0, 0),
    'tile_y': None,
    'to_zxnext': False,
    'zxn_fmt': zxn.Options.SL2
}


def sl2toimg(options):
    print("sl2toimg({})".format(options))
    foo = options.infile.read()
    options.infile.close()
    full_size = len(foo)
    data_size = 0

    if full_size in (6144, 6160, 6176):
        options.res = (128, 96)
        data_size = 6144
    elif full_size in (12288, 12544, 12800):
        data_size = 12288
        options.res = (128, 96)
    elif full_size in (49152, 48408, 49664):
        options.res = (256, 192)
        data_size = 49152
    elif full_size == 81920:
        data_size = 81920
        if options.res[0] != 640:
            options.res = (320, 256)
    elif full_size in (81936, 81952):
        data_size = 81920
        options.res = (640, 256)
    elif full_size in (82176, 82432):
        data_size = 81920
        options.res = (320, 256)
    else:
        sys.stderr.write("Malformed file\n")
        exit(1)
    pal_size = full_size - data_size

    if options.zxn_fmt in (options.SL2, options.SLR):
        pal = list(foo[data_size:])
        data = list(foo[:data_size])
    else:
        pal = list(foo[:pal_size])
        data = list(foo[pal_size:])

    if pal_size == 0:
        pal = list(np.asarray(zxn.palette(8))[:, :3].reshape((768,)))
    elif pal_size == 16:
        pal = zxn.pal8to24(pal) * 3
    elif pal_size == 32:
        pal = zxn.pal9to24(pal) * 3
    elif pal_size == 256:
        pal = zxn.pal8to24(pal)
    elif pal_size == 512:
        pal = zxn.pal9to24(pal)
    else:
        sys.stderr.write("Malformed file\n")
        exit(1)

    img = Image.new('P', options.res)
    img.putpalette(pal)
    if options.res[0] == 128 and data_size == 6144:
        data_m = np.empty((96, 64, 2))
        data = np.asarray(data).reshape((96, 64))
        data_a = data >> 4
        data_b = data & 15
        data_m[:, :, 0] = data_a
        data_m[:, :, 1] = data_b
        img.putdata(list(data_m.reshape((12288,))))
    elif options.res[0] in (128, 256):
        img.putdata(data)
    elif options.res[0] == 320:
        data = list(np.asarray(data).reshape((320, 256)).transpose().reshape((81920,)))
        img.putdata(data)
    else:
        data = np.asarray(data).reshape((320, 256)).transpose()
        data_a = data >> 4
        data_b = data & 15
        data = np.empty((256, 320, 2))
        data[:, :, 0] = data_a
        data[:, :, 1] = data_b
        data = data.reshape((163840,))
        img.putdata(data)

    return img


if __name__ == "__main__":
    options = zxn.Options(sys.argv, DEFAULTS)
    if options.verbose > 0:
        options.print()

    img = sl2toimg(options)

    if options.verbose > 1:
        img.resize((1024, 768)).show()
    try:
        img.save(options.outfile)
    except OSError:
        img.convert('RGB').save(options.outfile)

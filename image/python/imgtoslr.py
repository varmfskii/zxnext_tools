#!/usr/bin/env python3
import sys

import numpy as np

import zxntools as zxn

VERSION = "1.00.00"
DATE = "20210407"
NAME = 'imgtoslr'


def my_help(name):
    version()
    sys.stderr.write(
        ("Usage: {} [<options>] [<infile>] [<outfile>]\n"
         "\toptions are\n"
         "\t-d\t--dither\t\tuse dithering (dither)\n"
         "\t-h\t--help\t\tshow this help message\n"
         "\t-i\t--in\t\tinput file (stdin)\n"
         "\t-n\t--nodither\tdon't use dithering (dither)\n"
         "\t-o\t--out\t\toutput file (stdout)\n"
         "\t-p\t--pal\t\tpalette (P:NEXT)"
         "\t-r\t--radistan\t16 colour mode\n"
         "\t-s\t--scale\t\tscale image to fit\n"
         "\t-V\t--version\tget version information\n"
         "\t-v\t--verbose\tincrease verbosity\n"
         ).format(name))


def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)


DEFAULTS = {
    'opts': "dhi:no:p:rsVv",
    'long_opts': ['dither', 'help', 'in=', 'nodither', 'out=', 'pal=', '16', 'radistan', 'scale', 'version',
                  'verbose'],
    'inks': None,
    'papers': None,
    'pal_type': None,
    'num_colors': 256,
    'tile_y': None,
    'to_zxnext': True,
    'res': (128, 96),
    'zxn_fmt': zxn.Options.SLR,
    'help': my_help
}


def write_rad(img, options):
    data = np.asarray(img.getdata())
    data = data.reshape((6144, 2))
    data *= np.asarray((16, 1))
    data = np.int_(data.sum(axis=1))
    options.outfile.write(bytes(list(data)))
    if options.auto_palette or options.palette is not None:
        zxn.write_pal(img.getpalette(), 16, options.outfile)


def write_slr(img, options):
    options.outfile.write(bytes(list(img.getdata())))
    if options.auto_palette or options.palette is not None:
        zxn.write_pal(img.getpalette(), 256, options.outfile)


def imgtoslr(img, options):
    if options.auto_palette:
        img = zxn.auto_palette(img, options)
    elif options.palette is None:
        img = zxn.next_palette(img, options)
    else:
        img = img.quantize(palette=options.palette, dither=options.dither)
    if options.num_colors == 16:
        write_rad(img, options)
    else:
        write_slr(img, options)


if __name__ == "__main__":
    options = zxn.Options(sys.argv, DEFAULTS)
    img = zxn.get_image(options)
    imgtoslr(img, options)
    options.infile.close()
    options.outfile.close()

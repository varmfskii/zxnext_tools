#!/usr/bin/env python3
import sys

import numpy as np

import zxntools as zxn

VERSION = "1.00.00"
DATE = "20210407"
NAME = 'imgtosl2'


def my_help(name):
    version()
    sys.stderr.write(
        ("Usage: {} [<options>] [<infile>] [<outfile>]\n"
         "\toptions are\n"
         "\t-2\t--256x192\t256x192 resoultion\n"
         "\t-3\t--320x256\t320x192 resoultion\n"
         "\t-6\t--640x256\t640x192 resoultion\n"
         "\t-d\t--dither\t\tuse dithering (dither)\n"
         "\t-h\t--help\t\tshow this help message\n"
         "\t-i\t--in\t\tinput file (stdin)\n"
         "\t-n\t--nodither\tdon't use dithering (dither)\n"
         "\t-o\t--out\t\toutput file (stdout)\n"
         "\t-p\t--pal\t\tpalette (P:NEXT)"
         "\t-s\t--scale\t\tscale image to fit\n"
         "\t-V\t--version\tget version information\n"
         "\t-v\t--verbose\tincrease verbosity\n"
         ).format(name))


def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)


DEFAULTS = {'opts': "236dhi:no:p:rsVv",
            'long_opts': ['256', '256x192', '320', '320x256', '640', '640x256', 'dither', 'help', 'in=', 'nodither',
                          'out=', 'pal=', '16', 'radistan', 'scale', 'version', 'verbose'],
            'inks': None,
            'papers': None,
            'pal_type': None,
            'num_colors': 256,
            'tile_y': None,
            'res': (0, 0),
            'zxn_fmt': zxn.Options.SL2,
            'pal_first': False,
            'help': my_help
            }


def write_256(img, options):
    options.outfile.write(bytes(list(img.getdata())))


def write_320(img, options):
    data = np.asarray(img.getdata()).reshape((256, 320))
    data = data.transpose().reshape((320 * 256))
    options.outfile.write(bytes(list(data)))


def write_640(img, options):
    data = np.asarray(img.getdata()).reshape((256, 320, 2)) * np.asarray([16, 1])
    data = data.sum(axis=2).transpose().reshape((320 * 256))
    options.outfile.write(bytes(list(data)))


def write_palette(img, options):
    if options.zxn_fmt == options.NXI or options.auto_palette or options.palette is not None:
        zxn.write_pal(img.getpalette(), options.num_colors, options.outfile)


def imgtosl2(img, options):
    if options.res == (640, 256):
        options.num_colors = 16
    else:
        options.num_colors = 256

    if options.auto_palette:
        img = zxn.auto_palette(img, options)
    elif options.palette is None:
        img = zxn.next_palette(img, options)
    else:
        img = img.quantize(palette=options.palette, dither=options.dither)

    if options.pal_first:
        write_palette(img, options)

    if options.res == (256, 192):
        write_256(img, options)
    elif options.res == (320, 256):
        write_320(img, options)
    else:
        write_640(img, options)

    if not options.pal_first:
        write_palette(img, options)


if __name__ == "__main__":
    options = zxn.Options(sys.argv, DEFAULTS)

    if options.res == (0, 0):
        options.res = (256, 192)

    img = zxn.get_image(options)
    imgtosl2(img, options)
    options.infile.close()
    options.outfile.close()

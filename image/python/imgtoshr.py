#!/usr/bin/env python3
import sys
import zxntools as zxn

VERSION = "1.00.00"
DATE = "20210407"
NAME = 'imgtoshr'


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
         "\t-s\t--scale\t\tscale image to fit {}\n"
         "\t-V\t--version\tget version information\n"
         "\t-v\t--verbose\tincrease verbosity\n").format(name, False))


def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)


DEFAULTS = {
    'opts': "dhi:no:sVv",
    'long_opts': ['dither', 'help', 'in=', 'nodither', 'scale', 'version', 'verbose'],
    'inks': None,
    'papers': None,
    'pal_type': None,
    'num_colors': 2,
    'tile_y': 8,
    'to_zxnext': True,
    'res': (512, 192),
    'zxn_fmt': zxn.Options.SHR,
    'help': my_help
}


def imgtoshr(img, options):
    bm = img.convert('1', dither=options.dither)
    outfile = options.outfile

    left = [0] * 0x1800
    right = [0] * 0x1800

    for ar in range(24):
        for ac in range(32):
            for r in range(8):
                ix = (((ar & 0x18) | r) << 8) | ((ar & 7) << 5) | ac
                lt = 0xff
                rt = 0xff
                for c in range(8):
                    lt ^= bm.getpixel((ac * 16 + c, ar * 8 + r)) & (1 << (7 - c))
                    rt ^= bm.getpixel((ac * 16 + 8 + c, ar * 8 + r)) & (1 << (7 - c))
                left[ix] = lt
                right[ix] = rt

    outfile.write(bytes(left))
    outfile.write(bytes(right))


if __name__ == "__main__":
    options = zxn.Options(sys.argv, DEFAULTS)
    img = zxn.get_image(options)
    imgtoshr(img, options)
    options.infile.close()
    options.outfile.close()

#!/usr/bin/env python3
import sys

import imgtoscr as scr
import imgtoshr as shr
import imgtosl2 as sl2
import imgtoslr as slr
import zxntools as zxn

VERSION = "1.00.00"
DATE = "20210407"
NAME = 'imgtozxnext'


def my_help(name):
    version()
    sys.stderr.write(
        ("Usage: {} [<options>] [<infile>] [<outfile>]\n"
         "\tgeneral options are\n"
         "\t-d\t--dither\t\tuse dithering (dither)\n"
         "\t-h\t--help\t\tshow this help message\n"
         "\t-i\t--in\t\tinput file (stdin)\n"
         "\t-n\t--nodither\tdon't use dithering (dither)\n"
         "\t-o\t--out\t\toutput file (stdout)\n"
         "\t-p\t--pal\t\tpalette file (None)\n"
         "\t-s\t--scale\t\tscale image to fit\n"
         "\t-V\t--version\tget version information\n"
         "\t-v\t--verbose\tincrease verbosity\n"
         "\tscr/shc options\n"
         "\t\t--mc\t\tMC format timex hi-color file\n"
         "\t\t--mlt\t\tMLT format timex hi-color file\n"
         "\t\t--scr\t\tZX Spectrum screen dump\n"
         "\t\t--shc\t\tTimex hi-color screen dump\n"
         "\t-I\t--inks\t\tnumber of inks (ULA)\n"
         "\t-P\t--papers\tnumber of papers (ULA)\n"
         "\t-U\t--ula\t\tset palette type as ULA (ULA)\n"
         "\t-+\t--ulaplus\tset palette type as ULAplus (ULA)\n"
         "\tshr options\n"
         "\t\t--shr\t\tTimex hi-resolution screen dump\n"
         "\tsl2 options\n"
         "\t\t--nxi\t\tNext image file\n"
         "\t\t--sl2\t\tZX Next Layer 2 screen dump\n"
         "\t-2\t--256\t\t256x192x256 resoultion\n"
         "\t-3\t--320\t\t320x192x256 resoultion\n"
         "\t-6\t--640\t\t640x192x16 resoultion\n"
         "\tslr options\n"
         "\t\t--slr\t\tZX Next lo-resoulution screen dump\n"
         "\t-r\t--radistan\t16 colour mode\n"
         ).format(name))


def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)


DEFAULTS = {
    'opts': "236dDhHI:i:nNo:p:P:RsUVv+",
    'long_opts': ['256', '256x192', '320', '320x256', '640', '640x256', 'dither', 'help', 'hicolor', 'hicolour',
                  'inks=', 'in=', 'nodither', 'next', 'out=', 'pal=', 'papers=', '16', 'radistan', 'scale',
                  'ula', 'version', 'verbose', 'ulaplus', 'mc', 'mlt', 'nxi', 'scr', 'shc', 'shr', 'sl2',
                  'slr'],
    'inks': 16,
    'papers': 16,
    'pal_type': zxn.Options.ULA,
    'num_colors': 0,
    'tile_y': 8,
    'to_zxnext': True,
    'res': (0, 0),
    'zxn_fmt': zxn.Options.AUTO,
    'help': my_help
}

if __name__ == "__main__":
    options = zxn.Options(sys.argv, DEFAULTS)
    img = zxn.get_image(options)

    if options.zxn_fmt in (options.MC, options.MLT, options.SCR, options.SHC):
        scr.imgtoscr(img, options)
    elif options.zxn_fmt == options.SHR:
        shr.imgtoshr(img, options)
    elif options.zxn_fmt in (options.NXI, options.SL2):
        sl2.imgtosl2(img, options)
    elif options.zxn_fmt == options.SLR:
        slr.imgtoslr(img, options)
    else:
        sys.stderr.write("Unimplemented format\n")

    options.outfile.close()

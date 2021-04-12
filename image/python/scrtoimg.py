#!/usr/bin/env python3
from PIL import Image
import numpy as np
import zxntools as zxn
import sys

NAME = 'scrtoimg'
VERSION = '1.00.00'
DATE = "11 Apr 2021"


def my_help(name):
    version()
    sys.stderr.write(
        ("Usage: {} [<options>] [<infile>] [<outfile>]\n"
         "\toptions are\n"
         "\t-h\t--help\t\tshow this help message\n"
         "\t-i\t--in\t\tinput file (stdin)\n"
         "\t-o\t--out\t\toutput file (stdout)\n"
         "\t-p\t--pal\t\tpalette file (None)\n"
         "\t-V\t--version\tget version information\n"
         "\t-v\t--verbose\tincrease verbosity\n"
         ).format(name))


def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)


DEFAULTS = {
    'help': my_help,
    'inks': None,
    'long_opts': ['double', 'help', 'in=', 'out=', 'pal=', 'version', 'verbose'],
    'num_colors': None,
    'opts': 'hi:o:p:vV',
    'pal_type': None,
    'papers': None,
    'res': (256, 192),
    'tile_y': None,
    'to_zxnext': False,
    'zxn_fmt': zxn.Options.SCR
}


def ula_to_normal(data):
    data = data.reshape(3, 8, 8, 32)
    data_out = np.empty((192, 32), dtype=np.uint8)

    for r in range(192):
        r1 = r // 64
        r2 = (r // 8) & 7
        r3 = r & 7
        data_out[r] = data[r1, r3, r2]

    return data_out


def ula_attr():
    attr = np.empty((256, 2), dtype=np.uint8)

    for i in range(256):
        bright = (i >> 3) & 8
        ink = bright | (i & 7)
        paper = bright | ((i >> 3) & 7)
        attr[i, :] = np.asarray([paper, ink])

    return attr


def plus_attr():
    attr = np.empty((256, 2), dtype=np.uint8)

    for i in range(256):
        # mode = ((i & 128) >> 3) | ((i & 64) >>1)
        mode = ((i & 128) >> 2) | ((i & 64) >>2)
        ink = mode | (i & 7)
        paper = mode | 8 | ((i & 56) >> 3)
        attr[i, :] = np.asarray([paper, ink])

    return attr


def next_attr(inks):
    attr = np.empty((256, 2), dtype=np.uint8)
    mask_i = inks - 1
    mask_p = 255 - mask_i
    i = inks
    shift = 0

    while i > 1:
        shift += 1
        i >>= 1

    for i in range(256):
        ink = i & mask_i
        paper = inks + ((i & mask_p) >> shift)
        attr[i, :] = np.asarray([paper, ink])

    return attr


def scrtoimg(options):
    data_all = np.uint8(np.asarray(list(options.infile.read())))
    data_len = data_all.shape[0]
    pixel_data = np.uint8(data_all[:6144])

    if data_len < 12288:
        attr_data = np.uint8(data_all[6144:6912])
        pal_data = np.uint8(data_all[6912:])
    else:
        attr_data = np.uint8(data_all[6144:12288])
        pal_data = np.uint8(data_all[12288:])

    if options.ula_pixel:
        pixel_data = ula_to_normal(pixel_data)
    else:
        pixel_data = pixel_data.reshape((192, 32))

    if options.ula_attr and attr_data.shape[0] == 6144:
        attr_data = ula_to_normal(attr_data)
    else:
        if attr_data.shape[0] == 768:
            attr_data = attr_data.reshape((24, 32))
        else:
            attr_data = attr_data.reshape((192, 32))
    pixels = np.unpackbits(pixel_data, axis=1)

    img = Image.new('P', (256, 192))
    pal = None
    if pal_data.shape[0] == 0:
        if options.verbose > 0:
            print("ula")
        attr = ula_attr()
        print(zxn.ULACOLOURS.shape, zxn.ULACOLOURS.dtype)
        pal = list(zxn.ULACOLOURS[:, :3].reshape((48,))) * 16
    elif pal_data.shape[0] == 64:
        if options.verbose > 0:
            print("ula+")
        attr = plus_attr()
        pal = zxn.pal8to24(pal_data, plus=1)
        pal = pal*4
    else:
        inks = pal_data[0] + 1
        papers = 256 // inks
        attr = next_attr(inks)
        pal_data = pal_data[1:]
        if pal_data.shape[0] == inks + papers:
            if options.verbose > 0:
                print("ulanext 8-bit")
            pal = zxn.pal8to24(pal_data)
        elif (inks != 256 and pal_data.shape[0] == 2 * (inks + papers)) or (inks == 256 and pal_data.shape[0] == 513):
            if options.verbose > 0:
                print("ulanext 9-bit")
            pal = zxn.pal9to24(pal_data)
        else:
            sys.stderr.write("Malformed file\n")
            exit(1)
        colours = inks + papers
        pal = (pal * ((256 + colours - 1) // colours))[:768]
    pixels = pixels.reshape((192, 256))
    if attr_data.shape[0] == 24:
        # scr
        for y in range(24):
            yp = 8 * y
            for x in range(32):
                xp = 8 * x
                tile = pixels[yp:yp + 8, xp:xp + 8]
                tile = attr[attr_data[y, x], tile]
                pixels[yp:yp + 8, xp:xp + 8] = tile

    else:
        # shc
        for y in range(192):
            for x in range(32):
                xp = 8 * x
                tile = pixels[y, xp:xp + 8]
                tile = attr[attr_data[y, x], tile]
                pixels[y, xp:xp + 8] = tile

    img.putdata(list(pixels.reshape((49152,))))
    img.putpalette(pal)
    return img


if __name__ == "__main__":
    options = zxn.Options(sys.argv, DEFAULTS)

    if options.verbose > 0:
        options.print()

    img = scrtoimg(options)

    if options.verbose > 1:
        img.resize((1024, 768)).show()

    try:
        img.save(options.outfile)
    except OSError:
        img.convert('RGB').save(options.outfile)

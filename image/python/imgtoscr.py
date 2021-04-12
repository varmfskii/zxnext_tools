#!/usr/bin/env python3
import sys

import numpy as np
from PIL import Image
from numba import jit
import zxntools as zxn

# noinspection SpellCheckingInspection

NAME = 'imgtoscr'
VERSION = '1.00.00'
DATE = '20210407'


def my_help(name):
    version()
    sys.stderr.write(
        ("Usage: {} [<options>] [<infile>] [<outfile>]\n"
         "\toptions are\n"
         "\t-d\t--dither\t\tuse dithering (dither)\n"
         "\t-h\t--help\t\tshow this help message\n"
         "\t-I\t--inks\t\tnumber of inks (ULA)\n"
         "\t-i\t--in\t\tinput file (stdin)\n"
         "\t-U\t--ula\t\tset palette type as ULA (ULA)\n"
         "\t-n\t--nodither\tdon't use dithering (dither)\n"
         "\t-o\t--out\t\toutput file (stdout)\n"
         "\t-P\t--papers\tnumber of papers (ULA)\n"
         "\t-V\t--version\tget version information\n"
         "\t-v\t--verbose\tincrease verbosity\n"
         "\t-+\t--ulaplus\tset palette type as ULAplus (ULA)\n").format(name, False))


def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)


DEFAULTS = {
    'opts': "dhHI:i:no:p:P:sUVv+",
    'long_opts': ['dither', 'help', 'hicolor', 'hicolour', 'inks=', 'input=', 'nodither', 'output=', 'pal=',
                  'papers=', 'scale', 'ula', 'version', 'verbose', 'ulaplus'],
    'inks': 16,
    'papers': 16,
    'pal_type': zxn.Options.ULA,
    'num_colors': 32,
    'tile_y': 8,
    'res': (256, 192),
    'to_zxnext': True,
    'zxn_fmt': zxn.Options.SCR,
    'ula_pixel': True,
    'ula_attr': True,
    'help': my_help
}


def palette_to_image(palette):
    img = Image.new('P', (16, 16))
    colors = len(palette)
    imgpalette = []
    imgdata = []

    for i in range(256):
        imgpalette += list(palette[i % colors])
        imgdata.append(i % colors)

    img.putpalette(imgpalette)
    img.putdata(imgdata)
    return img


def get_attrs_plus(options):
    options.print()
    print("get_attrs_plus unimplemented")
    # 00xxxxxx
    # get 8 paper
    # get 8 ink
    # 11xxxxxx
    # get 8 paper
    # get 8 ink
    # 01xxxxxx
    # get 8 paper
    # get 8 ink
    # 10xxxxxx
    # get 8 paper
    # get 8 ink
    exit(0)


def get_attrs_next(options, img):
    if options.palette is not None:
        return pal_attr_next(options)
    else:
        return graph_attr_next(options, img)


def get_attrs_ula():
    attrs = []
    for paper in zxn.ZXNORMAL:
        for ink in zxn.ZXNORMAL:
            attrs.append((ink, paper))

    for paper in zxn.ZXBRIGHT:
        for ink in zxn.ZXBRIGHT:
            attrs.append((ink, paper))

    return attrs


def pal_attr_next(options):
    pal = np.asarray(options.palette.getpalette())[:, :3]
    inks = []
    papers = []
    attrs = []

    for i in range(options.inks):
        inks.append(pal[i])

    for p in range(128, options.papers + 128):
        papers.append(pal[p])

    for paper in papers:
        for ink in inks:
            attrs.append((ink, paper))

    return attrs


def graph_attr_next(options, img):
    temp_img = zxn.torgb9(img)
    colors = get_colors2(temp_img, options)
    papers = {}

    for r in range(8):
        for g in range(8):
            for b in range(8):
                papers[(r, g, b)] = 0

    for tile_colors in colors:
        max_col = (0, 0, 0)
        max_cnt = 0
        for key in tile_colors.keys():
            if tile_colors[key] > max_cnt:
                max_cnt = tile_colors[key]
                max_col = key

        papers[max_col] += max_cnt

    papers3, papers8 = reduce_colors(papers, options.papers)
    inks = {}

    for i in range(512):
        inks[(i >> 6, (i >> 3) & 7, i & 7)] = 0

    for tile_colors in colors:
        got_paper = False
        for key in tile_colors.keys():
            if got_paper or not tile_colors[key] in papers3:
                inks[key] += tile_colors[key]
                break
            got_paper = True

    inks3, inks8 = reduce_colors(inks, options.inks)
    attrs = []

    for paper in papers8:
        for ink in inks8:
            attrs.append((ink, paper))

    return attrs


def get_hist(img):
    i2 = img.convert('RGB')
    c = i2.getcolors()
    d = {}
    for i in c:
        d[i[1]] = i[0]
    return d


def get_dist1(attr, data):
    d1 = np.linalg.norm(zxn.CWT * (data - attr[0]), axis=1)
    d2 = np.linalg.norm(zxn.CWT * (data - attr[1]), axis=1)
    return np.minimum(d1, d2).sum()


def get_dist2(attr, data):
    attr = np.asarray(attr)
    d1 = data - attr[0]
    a1 = attr[1, :] - attr[0, :]
    a_len = a1.dot(a1)
    if a_len == 0:
        d = np.linalg.norm(zxn.CWT * d1, axis=1)
    else:
        t = d1.dot(a1) / a_len
        t[t < 0] = 0
        t[t > 1] = 1
        t2 = np.empty((data.shape,))
        t2[:, 0] = t * a1[0]
        t2[:, 1] = t * a1[1]
        t2[:, 2] = t * a1[2]
        d = np.linalg.norm(zxn.CWT * (d1 - t2), axis=1)
    dist = d.sum()
    # print(dist)
    return dist


@jit(nopython=True)
def get_dist3(attr, data):
    d = np.empty((data.shape[0]))
    for i in range(data.shape[0]):
        d[i] = np.minimum(np.linalg.norm(data[i] - attr[0]), np.linalg.norm(data[i] - attr[1]))
    return d.sum()


def get_disth(attr, data):
    attr = np.float32(attr)
    data = np.float32(data)
    return get_dist3(attr, data)


def get_attr_map(attrs, img, options):
    attr_map = np.empty((32 * 192 // options.tile_y), dtype=np.int8)
    tile_y = options.tile_y
    all_data = np.asarray(img.getdata(), dtype=np.float32).reshape((192, 256, 3))
    all_attrs = np.asarray(attrs, dtype=np.float32)

    ix = 0
    for y in range(0, 192, tile_y):
        for x in range(0, 256, 8):
            data = all_data[y:y + tile_y, x:x + 8, :].reshape((8 * tile_y, 3))
            min_attr = 0
            min_dist = get_dist(all_attrs[0, :], data)
            for i in range(1, len(attrs)):
                new_dist = get_dist(all_attrs[i, :], data)
                if new_dist < min_dist:
                    min_dist = new_dist
                    min_attr = i
            attr_map[ix] = min_attr
            ix += 1
            if options.verbose > 1:
                print("({}, {}): {}   ".format(y, x, min_attr), end='\r')

    if options.verbose > 1:
        print()

    return attr_map


def apply_attr_map(attrs, attr_map, img, options):
    attr_palette = []
    for attr in attrs:
        attr_palette.append(palette_to_image(attr))
    i = 0
    tile_y = options.tile_y
    out_img = Image.new('RGB', (256, 192))
    for y in range(0, 192, tile_y):
        for x in range(0, 256, 8):
            tile = img.crop((x, y, x + 8, y + tile_y))
            tile = tile.quantize(palette=attr_palette[attr_map[i]], dither=options.dither)
            out_img.paste(tile, (x, y))
            i += 1

    return out_img


def quantize(img, opts):
    colors = opts.num_colors
    img2 = Image.new('RGB', (256, 192))
    data = zxn.pal8to3(np.asarray(img.getdata()))
    d = []
    for e in data: d.append(tuple(e))
    img2.putdata(d)
    hist = get_hist(img2)
    colors3, colors8 = reduce_colors(hist, colors)
    palette = list(map(tuple, colors8))

    pp = []
    pal_len = len(palette)
    for i in range(256):
        pp.append(palette[i % pal_len][0])
        pp.append(palette[i % pal_len][1])
        pp.append(palette[i % pal_len][2])
    p = Image.new('P', (16, 16))
    p.putpalette(pp)
    p.putdata(list(range(256)))
    imgq = img.quantize(palette=p, dither=opts.dither)
    return imgq


def get_colors(img, options):
    imgq = quantize(img, options)
    return get_colors2(imgq, options)


def get_colors2(img, options):
    colors = []

    for y in range(0, 192, options.tile_y):
        for x in range(0, 256, 8):
            tile2 = img.crop((x, y, x + 8, y + options.tile_y))
            tile2 = tile2.quantize(colors=2, method=Image.MEDIANCUT, dither=options.dither)
            colors.append(get_hist(tile2))

    return colors


def reduce_colors(hist, count):
    graph = zxn.Graph()
    graph.build(hist)
    graph.reduce(count)
    colors3 = graph.nodes.keys()
    colors8 = []

    for key in colors3:
        color = zxn.pal3to8(np.int_(0.5 + graph.nodes[key].mean / zxn.CWT))
        colors8.append(color)

    return colors3, colors8


def write_pixels(img, attr_map, attrs, options):
    tile_y = options.tile_y
    pixels = np.empty((192, 32, 8))
    data = np.asarray(img.getdata()).reshape((192, 32, 8, 3))
    i = 0
    for y in range(0, 192, tile_y):
        for x in range(0, 32):
            ink = attrs[attr_map[i]][0]
            pixels[y:y + tile_y, x, :] = (data[y:y + tile_y, x, :] == ink).all(axis=2)
            i += 1

    pixels = pixels.reshape((192, 32, 8)).dot(np.asarray([128, 64, 32, 16, 8, 4, 2, 1]))
    if options.ula_pixel:
        write_ula_order(pixels, options.outfile)
    else:
        write_normal_order(pixels, options.outfile)


def write_ula_order(pixels, outfile):
    for sec in range(0, 192, 64):
        for row_y in range(8):
            for row in range(0, 64, 8):
                line = bytes(np.int8(pixels[sec + row_y + row]))
                outfile.write(line)


def write_normal_order(pixels, outfile):
    for row in range(0, 192):
        line = bytes(np.int8(pixels[row]))
        outfile.write(line)


def write_attr_map(attr_map, options):
    if options.tile_y == 8:
        options.outfile.write(bytes(attr_map))
    else:
        attr_map = np.asarray(attr_map).reshape((192, 32))
        if options.ula_attr:
            write_ula_order(attr_map, options.outfile)
        else:
            write_normal_order(attr_map, options.outfile)


def write_next_pal(attrs, options):
    weights = np.asarray([64, 8, 1])
    options.outfile.write(bytes([options.inks - 1]))
    inks = []
    papers = []

    for ink_ix in range(options.inks):
        ink = int(np.dot(zxn.pal8to3(np.asarray(attrs[ink_ix][0])), weights))
        inks.append(ink >> 1)
        inks.append(ink & 1)

    for ppr_ix in range(0, 256, options.inks):
        paper = int(np.dot(zxn.pal8to3(np.asarray(attrs[ppr_ix][1])), weights))
        papers.append(paper >> 1)
        papers.append(paper & 1)

    if options.papers == 1:
        papers.pop()

    if options.verbose > 0:
        print("inks")
        print(inks)
        print("papers")
        print(papers)

    options.outfile.write(bytes(inks))
    options.outfile.write(bytes(papers))


def write_plus_pal(attrs, outfile):
    print("write_plus_pal unimplemented {} {}".format(attrs, outfile))
    exit(0)


def write_scr(img, attr_map, attrs, options):
    if options.verbose > 1:
        img.resize((768, 576), resample=Image.NONE).show()
    write_pixels(img, attr_map, attrs, options)
    write_attr_map(attr_map, options)
    if options.pal_type == options.NEXT:
        write_next_pal(attrs, options)
    elif options.pal_type == options.PLUS:
        write_plus_pal(attrs, options.outfile)


def imgtoscr(img, options):
    img = img.convert('RGB')

    if options.is_ula():
        attrs = get_attrs_ula()
    elif options.is_next():
        attrs = get_attrs_next(options, img)
    else:
        colors = get_colors(img, options)
        attrs = get_attrs_plus(options, colors)

    if options.verbose > 0:
        print(len(attrs))

    attr_map = get_attr_map(attrs, img, options)
    imgo = apply_attr_map(attrs, attr_map, img, options)
    write_scr(imgo, attr_map, attrs, options)


get_dist = get_dist3

if __name__ == "__main__":
    options = zxn.Options(sys.argv, DEFAULTS)
    img = zxn.get_image(options)
    imgtoscr(img, options)
    options.infile.close()
    options.outfile.close()

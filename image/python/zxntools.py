import getopt

from PIL import Image
import sys
import numpy as np

ZXNV = 0x010000
ZXND = "20210411"

ZXNORMAL = np.asarray([(0x00, 0x00, 0x00),
                       (0x00, 0x00, 0xd7),
                       (0xd7, 0x00, 0x00),
                       (0xd7, 0x00, 0xd7),
                       (0x00, 0xd7, 0x00),
                       (0x00, 0xd7, 0xd7),
                       (0xd7, 0xd7, 0x00),
                       (0xd7, 0xd7, 0xd7)])
ZXBRIGHT = np.asarray([(0x00, 0x00, 0x00),
                       (0x00, 0x00, 0xff),
                       (0xff, 0x00, 0x00),
                       (0xff, 0x00, 0xff),
                       (0x00, 0xff, 0x00),
                       (0x00, 0xff, 0xff),
                       (0xff, 0xff, 0x00),
                       (0xff, 0xff, 0xff)])

ULACOLOURS = np.empty((16, 4), dtype=np.uint8)
ULACOLOURS[:8, :3] = ZXNORMAL
ULACOLOURS[8:, :3] = ZXBRIGHT
ULACOLOURS[:, 3] = 0xff

v3to8 = [0x00, 0x24, 0x48, 0x6d, 0x91, 0xb6, 0xda, 0xff]
v2to8 = [0x00, 0x55, 0xaa, 0xff]
pal1 = np.asarray([(0x00, 0x00, 0x00, 0xff), (0xff, 0xff, 0xff, 0xff)])
pal2 = np.asarray([(0x00, 0x00, 0x00, 0xff),
                   (0xff, 0x00, 0x00, 0xff),
                   (0x00, 0xff, 0xff, 0xff),
                   (0xff, 0xff, 0xff, 0xff)])
pal4 = ULACOLOURS

# CWT = np.asarray([0.299, 0.587, 0.114])
CWT = np.asarray([1, 1, 1])

verbose = 0


def setverbose(v):
    global verbose
    verbose = v


def getverbose():
    return verbose


def pow2(n):
    # bit manipulation to determine if number is a power of 2
    return n & (n - 1) == 0


# convert 8 bit values to 3 bit values
def pal8to3(color8):
    return (color8 * 14 + 255) // 510


# convert 3 bit values to 8 bit values
def pal3to8(color3):
    return (color3 * 510 + 7) // 14


def makepal(mixed):
    pal = Image.new('P', (16, 16))
    if len(mixed) == 256:
        xm = 1
        ym = 1
    elif len(mixed) == 128:
        xm = 2
        ym = 1
    elif len(mixed) == 64:
        xm = 2
        ym = 2
    elif len(mixed) == 32:
        xm = 4
        ym = 2
    elif len(mixed) == 16:
        xm = 4
        ym = 4
    elif len(mixed) == 8:
        xm = 8
        ym = 4
    elif len(mixed) == 4:
        xm = 8
        ym = 8
    elif len(mixed) == 2:
        xm = 16
        ym = 8
    elif len(mixed) == 1:
        xm = 16
        ym = 16
    else:
        xm = 1
        ym = 1

    pp = []
    for i in range(256):
        pp.append(mixed[i % len(mixed)][0])
        pp.append(mixed[i % len(mixed)][1])
        pp.append(mixed[i % len(mixed)][2])
    data = []
    for i in range(256):
        c = ((i % 16) // xm) * (16 // xm) + (i // 16) // ym
        data.append(c)
    pal.putpalette(pp)
    pal.putdata(data)
    return pal


def palette(n):
    if verbose > 1:
        sys.stderr.write("palette({})\n".format(n))

    if n == 1:
        return pal1
    elif n == 2:
        return pal2
    elif n == 4:
        return pal4
    elif n == 8:
        rv = []
        for i in range(256):
            rv.append((v3to8[(i >> 5) & 7], v3to8[(i >> 2) & 7], v2to8[i & 3], 255))
        return rv


def version(do_print):
    if do_print:
        sys.stderr.write(
            "ZX Next Tools (python) version {:d}.{:02d}.{:02d} {}\n".format(
                ZXNV >> 16, (ZXNV >> 8) & 0xff, ZXNV & 0xff, ZXND))
    return ZXNV


def readpal(palfile):
    data = list(palfile.read())
    pal = []
    while len(data) > 0:
        pal.append((data.pop(0), data.pop(0), data.pop(0), data.pop(0)))
    return makepal(pal)


def pal2to8(c):
    return c * 85


def pal8to2(c):
    return (c * 510 + 3) // 6


def torgb9(img):
    data = np.asarray(img.getdata())
    data = pal8to3(data)
    temp_img = Image.new('RGB', img.size)
    temp_img.putdata(list(map(tuple, list(data))))
    return temp_img


def auto_palette(img, options):
    data = np.asarray(img.getdata())
    data = pal8to3(data)
    data = list(map(tuple, list(data)))
    pal_img = Image.new('RGB', options.res)
    pal_img.putdata(data)
    pal_img = pal_img.quantize(colors=options.num_colors, dither=Image.NONE)
    pal = np.asarray(pal_img.getpalette())[:options.num_colors * 3]
    pal = pal3to8(pal)
    pal_img.putpalette(list(pal) * (256 // options.num_colors))
    return img.quantize(palette=pal_img, dither=options.dither)


def write_pal(palette, number, outfile):
    pal = pal8to3(np.asarray(palette).reshape((256, 3)))[:number, :]
    pal *= np.asarray((64, 8, 1))
    pal = list(np.int_(pal.sum(axis=1)))
    print(len(pal))
    for color in pal:
        outfile.write(bytes([color >> 1, color & 1]))


def next_palette(img, options):
    if options.num_colors == 16:
        pal = palette(4)
    else:
        pal = palette(8)

    pal = makepal(np.int_(pal))
    return img.quantize(palette=pal, dither=options.dither)


class Graph:
    def __init__(self):
        self.nodes = {}
        self.edges = set()

    def add_edge(self, n1, n2):
        self.edges.add((n1, n2, self.get_wvar(n1, n2)))

    def merge(self, t):
        n1, n2, wvar = t
        if n1.weight == 0:
            n1.sum1 = n2.sum1
            n1.sum2 = n2.sum2
            n1.weight = n2.weight
            n1.mean = n2.mean
            n1.wvar = n2.wvar
        else:
            n1.sum1 += n2.sum1
            n1.sum2 += n2.sum2
            n1.weight += n2.weight
            n1.mean = n1.sum1 / n1.weight
            var = (n1.sum2 - n1.sum1 * n1.mean) / n1.weight
            var[var < 0] = 0
            n1.wvar = np.sqrt(var.sum()) * n1.weight

        edge_list = list(self.edges)

        for edge in edge_list:
            if edge[0] in (n1, n2) or edge[1] in (n1, n2):
                self.edges.remove(edge)
                if edge[0] not in (n1, n2):
                    self.edges.add((edge[0], n1, self.get_wvar(edge[0], n1)))
                elif edge[1] not in (n1, n2):
                    self.edges.add((n1, edge[1], self.get_wvar(n1, edge[1])))

        del self.nodes[n2.key]

    def delete_node(self):
        min_wvar = float('inf')
        min_edges = []

        for edge in self.edges:
            if edge[2] == min_wvar:
                min_edges.append(edge)
            elif edge[2] < min_wvar:
                min_wvar = edge[2]
                min_edges = [edge]

        self.merge(min_edges[np.random.randint(len(min_edges))])

    @staticmethod
    def get_wvar(n1, n2):
        if n1.weight == 0:
            return n2.wvar

        if n2.weight == 0:
            return n1.wvar

        sum1 = n1.sum1 + n2.sum1
        sum2 = n1.sum2 + n2.sum2
        weight = n1.weight + n2.weight
        mean = sum1 / weight
        var = sum2 / weight - mean * mean
        return np.sqrt(np.sum(var)) * weight

    def build(self, hist):
        for c in range(512):
            r = (c >> 6)
            g = (c >> 3) & 7
            b = c & 7
            color = (r, g, b)

            if color in hist.keys():
                node = Node(self, color, hist[color])
            else:
                node = Node(self, color, 0)

            if r > 0:
                node2 = self.nodes[(r - 1, g, b)]
                self.add_edge(node, node2)

            if g > 0:
                node2 = self.nodes[(r, g - 1, b)]
                self.add_edge(node, node2)

            if b > 0:
                node2 = self.nodes[(r, g, b - 1)]
                self.add_edge(node, node2)

    def reduce(self, num_colors):
        while len(self.nodes) > num_colors:
            self.delete_node()


class Node:
    def __init__(self, graph, color, weight):
        self.graph = graph
        self.key = color
        self.weight = weight
        self.mean = np.asarray(color) * CWT
        self.wvar = 0
        self.sum1 = self.mean * weight
        self.sum2 = self.mean * self.mean * weight
        graph.nodes[color] = self


class Options:
    ULA = 0
    NEXT = 1
    PLUS = 2
    AUTO = 0
    SCR = 1
    SHC = 2
    SHR = 3
    SL2 = 4
    SLR = 5
    NXI = 6
    MC = 7
    MLT = 8
    EXTMAP = {'MC': (MC, (256, 192), False, False, False, 1), 'MLT': (MLT, (256, 192), False, True, False, 1),
              'NXI': (NXI, (256, 192), True, True, True, 0), 'SCR': (SCR, (256, 192), False, True, True, 8),
              'SHC': (SHC, (256, 192), False, True, True, 1), 'SHR': (SHR, (512, 192), False, True, True, 0),
              'SL2': (SL2, (0, 0), False, True, True, 0), 'SLR': (SLR, (128, 96), False, True, True, 0)}

    def __init__(self, args, defaults):
        opts = defaults['opts']
        long_opts = defaults['long_opts']
        in_name = None
        out_name = None
        pal_name = None
        res = (256, 192)
        self.auto_palette = False
        self.dither = Image.FLOYDSTEINBERG
        self.double = False
        self.inks = defaults['inks']
        self.num_colors = defaults['num_colors']
        self.zxn_fmt = defaults['zxn_fmt']
        self.palette = None
        self.pal_first = False
        self.pal_next = True
        self.pal_type = defaults['pal_type']
        self.papers = defaults['papers']
        self.res = defaults['res']
        self.scale = False
        self.tile_y = defaults['tile_y']
        self.to_zxnext = defaults['to_zxnext']
        self.ula_attr = True
        self.ula_pixel = True
        self.verbose = 0
        self.my_help = defaults['help']

        optlist, arglist = getopt.getopt(args[1:], opts, long_opts)

        for opt, arg in optlist:
            if opt in ('-2', '--256', '--256x192'):
                res = (256, 192)
            elif opt in ('-3', '--320', '--320x256'):
                res = (320, 256)
            elif opt in ('-6', '--640', '--640x256'):
                res = (640, 256)
            elif opt in ('-d', '--dither'):
                self.dither = Image.FLOYDSTEINBERG
            elif opt in ('-D', '--double'):
                self.double = True
            elif opt in ('-h', '--help'):
                self.my_help(args[0])
                exit(0)
            elif opt in ('-H', '--hicolor', '--hihcolour'):
                self.tile_y = 1
            elif opt in ('-i', '--in'):
                in_name = arg
            elif opt in ('-I', '--inks'):
                i = int(arg)
                if i > 256 or i < 2 or not pow2(i):
                    sys.stderr.write("Illegal number of inks {}\n".format(i))
                    exit(1)
                self.papers = 256 // i
                self.inks = i
                self.num_colors = self.inks + self.papers
                self.pal_type = self.NEXT
            elif opt in ('-n', '--nodither'):
                self.dither = Image.NONE
            elif opt in ('-N', '--next'):
                self.pal_next = False
            elif opt in ('-o', '--out'):
                out_name = arg
            elif opt in ('-P', '--papers'):
                p = int(arg)
                if p > 128 or p < 1 or not pow2(p):
                    sys.stderr.write("Illegal number of papers {}\n".format(p))
                    exit(1)
                self.papers = p
                self.inks = 256 // p
                self.pal_type = self.NEXT
                self.num_colors = self.inks + self.papers
            elif opt in ('-p', '--pal'):
                if arg.upper() == 'P:AUTO':
                    self.auto_palette = True
                    pal_name = None
                elif arg.upper() == 'P:NEXT':
                    self.auto_palette = False
                    pal_name = None
                elif arg.upper()[:2] == 'F:':
                    self.auto_palette = False
                    pal_name = arg[2:]
                else:
                    pal_name = arg
            elif opt in ('-r', '--16', '--radistan'):
                self.num_colors = 16
            elif opt in ('-s', '--scale'):
                self.scale = True
            elif opt in ('-U', '--ula'):
                self.pal_type = self.ULA
            elif opt in ('-V', '--version'):
                version()
                exit(0)
            elif opt in ('-v', '--verbose'):
                self.verbose += 1
            elif opt in ('-+', '--ulaplus'):
                self.pal_type = self.PLUS
            elif opt[:2] == '--' and opt[2:].upper in self.EXTMAP.keys():
                self.set_from_map(opt[2:].upper())
            else:
                sys.stderr.write("Illegal option {}\n", opt)
                exit(1)

        if len(arglist) > 0 and in_name is None:
            in_name = arglist.pop(0)

        if len(arglist) > 0 and out_name is None:
            out_name = arglist.pop(0)

        if in_name is None:
            self.infile = sys.stdin
        else:
            try:
                self.infile = open(in_name, 'rb')
            except OSError:
                sys.stderr.write("Unable to open {}\n".format(in_name))

        if out_name is None:
            self.outfile = sys.stdout
        else:
            try:
                self.outfile = open(out_name, 'wb')
            except OSError:
                sys.stderr.write("Unable to open {}\n".format(out_name))

        if pal_name is not None:
            try:
                palfile = open(pal_name, 'rb')
                self.palette = readpal(palfile)
            except OSError:
                sys.stderr.write("Unable to open {}\n".format(pal_name))

        if self.to_zxnext and self.zxn_fmt == self.AUTO:
            if out_name is None:
                self.zxn_fmt = self.SCR
            else:
                ext = out_name.split('.')[-1].upper()

                if ext in self.EXTMAP:
                    self.set_from_map(ext)
                else:
                    self.set_from_map('SCR')

                if self.res == (0, 0):
                    self.res = res
        else:
            if in_name is None:
                self.zxn_fmt = self.SCR
            else:
                ext = in_name.split('.')[-1].upper()

                if ext in self.EXTMAP:
                    self.set_from_map(ext)
                else:
                    self.set_from_map('SCR')

                if self.res == (0, 0):
                    self.res = res

        setverbose(self.verbose)

    def set_from_map(self, ext):
        self.zxn_fmt = self.EXTMAP[ext][0]
        self.res = self.EXTMAP[ext][1]
        self.pal_first = self.EXTMAP[ext][2]
        self.ula_pixel = self.EXTMAP[ext][3]
        self.ula_attr = self.EXTMAP[ext][4]
        self.tile_y = self.EXTMAP[ext][5]

    def is_next(self):
        return self.pal_type == self.NEXT

    def is_plus(self):
        return self.pal_type == self.PLUS

    def is_ula(self):
        return self.pal_type == self.ULA

    def print(self):
        print('dither:', self.dither == Image.FLOYDSTEINBERG)
        print('infile:', self.infile)
        print('outfile:', self.outfile)
        print('palette:', self.palette)
        print('scale:', self.scale)
        print('verbose:', self.verbose)

        if self.zxn_fmt == self.SCR:
            print('zxn_fmt: SCR')
            self.print_scr_shc()
        elif self.zxn_fmt == self.SHC:
            print('zxn_fmt: SHC')
            self.print_scr_shc()
        elif self.zxn_fmt == self.SHR:
            print('zxn_fmt: SHR')
        elif self.zxn_fmt == self.SL2:
            print('zxn_fmt: SL2')
            print('resolution:', self.res)
        elif self.zxn_fmt == self.SLR:
            print('zxn_fmt: SLR')
            if self.num_colors == 16:
                print('colours: 16')
            else:
                print('colours: 256')
        elif self.zxn_fmt == self.AUTO:
            print('zxn_fmt: AUTO')
        else:
            print('zxn_fmt: ', self.zxn_fmt)

    def print_scr_shc(self):
        if self.pal_type == self.NEXT:
            print('pal_type: ULANext')
            print('inks:', self.inks)
            print('papers:', self.papers)
        elif self.pal_type == self.PLUS:
            print('pal_type: ULAPLus')
        else:
            print('pal_type: ULA')


def get_image(options):
    img = Image.open(options.infile)

    if options.scale:
        img = img.resize(options.res)
    else:
        x, y = options.res
        img = img.crop((0, 0, x, y))

    if options.verbose > 0:
        options.print()

    return img


def pal8to24(pal, plus=0):
    pal_len = len(pal)
    pal_m = np.asarray(list(pal))
    pal = np.empty((pal_len, 3), dtype=np.uint8)
    pal[:, plus] = pal3to8(pal_m >> 5)
    pal[:, plus-1] = pal3to8((pal_m >> 2) & 7)
    pal[:, 2] = pal2to8(pal_m & 3)
    pal = pal.reshape((3 * pal_len))
    return list(pal)


def pal9to24(pal):
    pal_len = len(pal) // 2
    pal = list(pal)
    pal_m = np.asarray(pal).reshape((pal_len, 2)).dot((2, 1))
    pal = np.empty((pal_len, 3), dtype=np.uint8)
    pal[:, 0] = pal_m >> 6
    pal[:, 1] = (pal_m >> 3) & 7
    pal[:, 2] = pal_m & 7
    pal = np.uint8(pal3to8(pal)).reshape((3 * pal_len))
    return list(pal)


if __name__ == "__main__":
    print("Library, do not call directly")

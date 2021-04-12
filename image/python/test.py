#!/bin/env python3
from PIL import Image
import sys
import zxntools as zxn
import copy
import math
import getopt

NAME = 'imgtoscr'
VERSION = '1.00.00'
DATE = '20210326'

def c8to3(c):
    return ((c*14+1)//510*510+7)//14


def t8to3(rgb):
    return (c8to3(rgb[0]),c8to3(rgb[1]),c8to3(rgb[2]))


def hist(img):
    i2 = img.convert('RGB')
    c = i2.getcolors()
    d = {}
    for i in c:
        d[i[1]]=i[0]
    #print(d)
    return d


def getdist(attr, colors):
    dist = 0
    a = attr.getpalette()
    #print(a, colors)
    for k in colors.keys():
        da = 0
        db = 0
        for i in range(3):
            d = a[i]-k[i]
            da += d*d
            d = a[3+i]-k[i]
            db += d*d

        if da>db:
            dist += math.sqrt(db)*colors[k]
        else:
            dist += math.sqrt(da)*colors[k]

    return dist


def help(name):
    version()
    sys.stderr.write(
"""Usage: {} [<options>] [<infile>] [<outfile>]
	options are
	-h	--help		show this help message
	-I	--inks		number of inks (ULA)
	-i	--in		input file (stdin)
	-U	--ula		set palette type as ULA (ULA)
	-o	--out		output file (stdout)
	-P	--papers	number of papers (ULA)
	-S	--share		share palette entries ({})
	-V	--version	get version information
	-v	--verbose	increase verbosity
	-+	--ulaplus	set palette type as ULAplus (ULA)
""".format(name, False))

    
def version():
    sys.stderr.write("{} version {} {}\n".format(NAME, VERSION, DATE))
    zxn.version(True)

    
class Options:
    ULA = 0
    NEXT = 1
    PLUS = 2
    
    def __init__(self, args):
        opts = "hI:i:o:P:SUVv+"
        longopts = ['help', 'inks=', 'input=', 'output=', 'papers=', 'share',
                    'ula', 'version', 'verbose', 'ulaplus']
        inname = None
        outname = None
        self.verbose = 0
        self.inks = 16
        self.papers = 16
        self.paltype = self.ULA
        self.shared = False
        
        optlist, arglist = getopt.getopt(args[1:], opts, longopts)

        for opt, arg in optlist:
            if opt in ('-h', '--help'):
                help(args[0])
            elif opt in ('-I', '--inks'):
                i = int(arg)
                if i!=256 and i!=128 and i!=64 and i!=32 and i!=16 and i!=8 and i!=4 and i!=2:
                    sys.stderr.write("Illegal number of inks {}\n".version(p))
                    exit(1)
                self.papers = 256//i
                self.inks = i
                self.paltype = self.NEXT
            elif opt in ('-i', '--input'):
                inname = arg
            elif opt in ('-o', '--output'):
                outname = arg
            elif opt in ('-P', '--papers'):
                p = int(arg)
                if p!=128 and p!=64 and p!=32 and p!=16 and p!=8 and p!=4 and p!=2 and p!=1:
                    sys.stderr.write("Illegal number of papers {}\n".version(p))
                    exit(1)
                self.papers = p
                self.inks = 256//p
                self.paltype = self.NEXT
            elif opt in ('-S', '--share'):
                self.shared = True
            elif opt in ('-U', '--ula'):
                self.paltype = self.ULA
            elif opt in ('-V', '--version'):
                version()
                exit(0)
            elif opt in ('-v', '--verbose'):
                self.verbose += 1
            elif opt in ('-+', '--ulaplus'):
                self.paltype = self.PLUS
            else:
                sys.stderr.write("Illegal option {}\n", opt)
                exit(1)

        if len(arglist)>0 and inname==None:
            inname = arglist.pop(0)
            
        if len(arglist)>0 and outname==None:
            outname = arglist.pop(0)

        if inname==None:
            self.infile = sys.stdin
        else:
            self.infile=open(inname, 'rb')
        
        if outname==None:
            self.outfile = sys.stdout
        else:
            self.outfile=open(outname, 'wb')

            
    def print(self):
        print('infile:', self.infile)
        print('outfile:', self.outfile)
        print('verbose:', self.verbose)
        print('papers:', self.papers)
        print('inks:', self.inks)


        
options = Options(sys.argv)
options.print()
exit(0)

if len(sys.argv)>2:
    numinks = int(sys.argv[2])
    numpapers = 256//numinks
else:
    numinks = 16
    numpapers = 16
img1 = Image.open(sys.argv[1]).resize((256,192))
#img1.resize((768,576),resample=Image.NEAREST).show()
img2 = Image.new('RGB',(256,192))
img3 = Image.new('RGB',(256,192))
data = list(img1.getdata())
img2.putdata(list(map(t8to3, list(img1.getdata()))))
#img2.resize((768,576),resample=Image.NEAREST).show()
if len(sys.argv)>3:
    if numinks>numpapers:
        img2 = img2.convert('RGB').quantize(colors=numinks, method=Image.MAXCOVERAGE)
    else:
        img2 = img2.convert('RGB').quantize(colors=numpapers, method=Image.MAXCOVERAGE)
elif numinks+numpapers<256:
    img2 = img2.convert('RGB').quantize(colors=numinks+numpapers, method=Image.MAXCOVERAGE)
else:
    img2 = img2.convert('RGB').quantize(colors=256, method=Image.MAXCOVERAGE)
#print(img2.histogram())
#img2.resize((768,576),resample=Image.NEAREST).show()
colors=[]
for y in range(0,192,8):
    for x in range(0,256,8):
        tile2 = img2.crop((x,y,x+8,y+8))
        tile2 = tile2.quantize(colors=2,method=Image.MAXCOVERAGE)
        img3.paste(tile2,(x,y))
        colors.append(hist(tile2))

#print(img3.histogram())
#img3.resize((768,576),resample=Image.NEAREST).show()
        
c1 = colors
#print(len(c1))
papers=[]
for p in range(numpapers):
    d = {}
    
    for l in c1:
        for c in l.keys():
            if c in d:
                d[c] += l[c]
            else:
                d[c] = l[c]

    mx = ((0,0,0), 0)
    for k in d.keys():
        if d[k]>mx[1]:
            mx = (k,d[k])

    papers.append(mx[0])
    
    c2 = []
    for c in c1:
        if not mx[0] in c.keys():
            c2.append(c)

    c1 = c2
    #print(len(c1),mx[0])

#exit(0)
c1 = copy.deepcopy(colors)
for l in c1:
    for p in papers:
        if p in l.keys():
            del l[p]
            break

c2 = []
for l in c1:
    if l!={}:
        c2.append(l)

c1 = c2
#print(len(c1))
#print(c1)
inks=[]
for i in range(numinks):
    d = {}
    
    for l in c1:
        for c in l.keys():
            if c in d:
                d[c] += l[c]
            else:
                d[c] = l[c]

    mx = ((0,0,0), 0)
    for k in d.keys():
        if d[k]>mx[1]:
            mx = (k,d[k])

    inks.append(mx[0])
    
    c2 = []
    for c in c1:
        if not mx[0] in c.keys():
            c2.append(c)

    c1 = c2
    #print(len(c1),mx[0])

#print(list(img3.getcolors()))
#print(papers)
#print(inks)

attrs = []
for i in inks:
    for p in papers:
        attr = Image.new('P',(1,2))
        pal = []
        for x in range(128):
            pal = pal+list(p)
            pal = pal+list(i)
        attr.putpalette(pal)
        attr.putdata([0, 1])
        attrs.append(attr)
        
attr_map = []
#print(colors)
for c in colors:
    least = attrs[0]
    dist = getdist(attrs[0], c)
    for attr in attrs:
        d2 = getdist(attr, c)
        if d2<dist:
            dist = d2
            least = attr
    attr_map.append(least)

img3.resize((768,557),resample=Image.NEAREST).show()

img2 = img2.convert('RGB')

img4 = Image.new('RGB',(256,192))
i = 0
for y in range(0,192,8):
    for x in range(0,256,8):
        tile = img2.crop((x,y,x+8,y+8))
        img4.paste(tile.quantize(palette=attr_map[i]),(x,y))
        i += 1

img4.resize((768,557),resample=Image.NEAREST).show()

img5 = Image.new('RGB',(256,192))
i = 0
for y in range(0,192,8):
    for x in range(0,256,8):
        tile = img3.crop((x,y,x+8,y+8))
        img5.paste(tile.quantize(palette=attr_map[i]),(x,y))
        i += 1
        
img5.resize((768,557),resample=Image.NEAREST).show()



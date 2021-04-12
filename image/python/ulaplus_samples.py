#!/usr/bin/env python3

def write_image(name, pix, atr, pal):
    file = open(name, 'wb')
    file.write(pix)
    file.write(atr)
    file.write(pal)
    file.close()


pixels = [0x00] * 2048
pixels += ([0xaa] * 256 + [0x55] * 256) * 4
pixels += [0xff] * 2048
pixels = bytes(pixels)
attrs = bytes(range(256)) * 3
palette = []

for g in range(4):
    gb = ((g * 14 + 3) // 6) << 5
    for r in range(4):
        rb = ((r * 14 + 3) // 6) << 2
        for b in range(4):
            bb = b
            palette.append(gb + rb + bb)

palette = bytes(palette)
write_image('sample1+.scr', pixels, attrs, palette)
row_ink = [0xff] * 32
row_paper = [0xff] * 4 + [0x00] * 24 + [0xff] * 4
pixels = (row_ink * 3 + row_paper * 3 + row_ink * 2) * 8
pixels += (row_ink + row_paper * 3 + row_ink * 3 + row_paper) * 8
pixels += (row_paper * 2 + row_ink * 3 + row_paper * 3) * 8
pixels = bytes(pixels)
attrs = []

for row in range(24):
    mode = (row // 6) << 6
    attrs += [0x00] * 4
    for x in range(0, 72, 9):
        attrs += [mode | x] * 3
    attrs += [0x00] * 4

attrs = bytes(attrs)
write_image('sample2+.scr', pixels, attrs, palette)

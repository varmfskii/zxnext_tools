# zxncreator

A program to assemble .zxn files

zxn files are binaries for the ZX Spectrum Next. They are inspired in
part by the IFF format widely used by Amiga software (this was the
basis for RIFF files). They consist of a magic number (4-bytes) "ZXFF"
folllowed by a number of blocks.  Each block starts with an 8 byte
header by up to 8k in data. The format of the header depends on the
block type and the data is intepreted according to the block type.

## block types

## block type $00 - Id block

- $0000 - $00 (block type $00)
- $0001 - version
- $0002-$0003 - length ($0008)
- $0004-$0007 - ZX Spectrum Next version
- $0008-$000b - ZXFF Version


### block type $00 - standard data

- $0000 - $01 (block type $00)
- $0001 - version
- $0002-$0003 - length
- $0004 - mmu page
- $0005 - reserved
- $0006-$0007 - start address within page ($0000 to $1fff)
- $0008-end - data

The data will be written into the given MMU page starting at the start
address

### block type $02 - execute

- $0000 - $01 (block type $01)
- $0001 - version
- $0002-$0003 - length ($000e)
- $0004 - page mask (which pages to actually set)
- $0005 - reserved
- $0006 - page 0
- $0007 - page 1
- $0008 - page 2
- $0009 - page 3
- $000a - page 4
- $000b - page 5
- $000d - page 6
- $000d - page 7
- $000e-$000f - SP ($0000 = don't set)
- $0010-$0011 - PC ($0000 = don't set, return after loading)

Page in the page for page 7, copy link code to top of page 7, page in
all pages other than that occupied by loader. Call link code at top of
page 7 ($ff00?). Iink code: Pages in the program page that was kept
out by loader. Sets the stack pointer. And calls the PC location. If
execution returns, the rest of the link code: pages the loader back in
and returns execution to it.

### block type $ff - comment

$0000 - $ff (block type $ff)
$0001 - version
$0002-$0003 - length
$0004-$0007 - reserved
$0008-end - data

## Note

Currently no software exists to either create or execute .zxn
files. This document exists as preliminary documentation for
comment. For those unfamiliar with IFF or RIFF (or AIFF) files, the
basic idea is that a file consists of a number of these
blocks. Generally, when an application loads the file, it processes
the blocks it recognizes and ignores the blocks it doesn't recognize.

These blocks are for executable files.  Simple additions can be made
for other types of data with more specific functions (for example:
screen image files, tile sets, sprite data, audio files, etc.)

# zxncreator

A program to assemble .zxn files

zxn files are binaries for the ZX Spectrum Next. They are inspired in
part by the IFF format widely used by Amiga software. They consist of
a 32 byte header and a set of blocks. Each block starts with an 8 byte
header by up to 8k in data. The format of the header depends on the
block type and the data is intepreted according to the block type.

## header

$0000-$0003 - ZXNX
$0004-$0007 - ZX Spectrum Next version
$0008-$000b - ZXNX version
$000c-$000d - SP ($0000 = don't set)
$000e-$000f - PC ($0000 = don't set, return after loading)
$0010 - page 0
$0011 - page 1
$0012 - page 2
$0013 - page 3
$0014 - page 4
$0015 - page 5
$0016 - page 6
$0017 - page 7
$0018-$0019 - block count
$001a-$001f - reserved

## block types

### block type $00 - standard data

- $0000 - $00 (block type $00)
- $0001 - version
- $0002-$0003 - length
- $0004 - mmu page
- $0005 - reserved
- $0006-$0007 - start address within page ($0000 to $1fff)
- $0008-end - data

The data will be written into the given MMU page starting at the start
address

### block type $01 - port data (individual)

- $0000 - $01 (block type $01)
- $0001 - version
- $0002-$0003 - length
- $0004-$0005 - count (number of port writes)
- $0006-$0007 - reserved
- $0008-end triples
  - 2-bytes port number
  - 1-byte port data

The data will be loaded into the given 16-bit ports

### block type $02 - port data (block 8)

- $0000 - $02 (block type $02)
- $0001 - version
- $0002-$0003 - length
- $0004 - port number
- $0005 - $00
- $0006-$0007 - reserved
- $0008-end - data

The data will be loaded into the indicated 8-bit I/O port

### block type $03 - port data (block 16)

- $0000 - $03 (block type $03)
- $0001 - version
- $0002-$0003 - length
- $0004-$0005 - port number
- $0006-$0007 - reserved
- $0008-end - data

The data will be loaded into the indicated 16-bit I/O port

### block type $04 - next register data (individual)

- $0000 - $05 (block type $04)
- $0001 - version
- $0002-$0003 - length
- $0004-$0007 - reserved
- $0008-end - data pairs
  - 1-byte register number
  - 1-byte value

The data will be loaded into the given ZX Next registers

### block type $05 - next register data (block)

- $0000 - $05 (block type $05)
- $0001 - version
- $0002-$0003 - length
- $0004 - register number
- $0005 - $00
- $0006-$0007 - reserved
- $0008-end - data

The block data will be loaded into the indicated ZX Next register

### block type $06 - immediate code

- $0000 - $06 (block type $06)
- $0001 - version
- $0002-$0003 - length
- $0004-$0005 - SP
- $0006-$0007 - reserved
- $0008-end - code

The block will be loaded into highest available MMU page which will be
located at address $e000. The stack pointer will be set to $ff02
($ff00 and $ff01 will contain the return address) and program
control will then jump to $e000 expecting an rts to return control to
the loader.

### block type $ff - comment

$0000 - $ff (block type $ff)
$0001 - version
$0002-$0003 - length
$0004-$0007 - reserved
$0008-end - data

## Note

currently no software exists to either create or execute .zxn
files. This document exists as preliminary documentation for comment.

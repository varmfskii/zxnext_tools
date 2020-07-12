showsimg format information

In all cases anything other than image data and colour attribute data
(where applicable) are optional.

SCR:
* 6144 bytes image data
* 768 bytes colour attribute data
* 1 byte ULANext attribute
* Palette data

SHC:
* 6144 bytes image data
* 6144 bytes colour attribute data
* 1 byte ULANext attribute
* Palette data

SHR:
* 12288 bytes image data
* 1 byte hires colour pair
* Palette data

SL2: 256x192x8
* 49152 bytes image data
* Palette data

NXI: 256x192x8
* 512 bytes palette data
* 49152 bytes image data

SL2: 320x256x8
* 81920 bytes image data
* Palette data

SL2: 640x256x4
* 81920 bytes image data
* Palette data

SLR: 128x96x8
* 12288 bytes image data
* Palette data

SL2: 128x96x4 (Radastan)
* 6144 bytes image data
* Palette data

Palette data:
* ULAplus: 64 bytes
* ULANext:
 - Attr 0x01: 130/260 bytes
 - Attr 0x03: 68/136 bytes
 - Attr 0x07: 40/80 bytes
 - Attr 0x0f: 32/64 bytes
 - Attr 0x1f: 40/80 bytes
 - Attr 0x3f: 68/136 bytes
 - Attr 0x7f: 130/260 bytes
* 16 colour: 16/32 bytes
* 256 colour: 256/512 bytes


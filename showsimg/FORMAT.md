Spectrum family image formats supported by .showsimg

SCR: classic ZX Spectrum screen dump (256x192)

* 6144 bytes of image data in Spectrum Order
  * 768 bytes of colour attribute data
  * Optionally a ULAplus or ULANext extension


SHC: Timex Hi-Color screen dump (256x192)

  * 6144 bytes image data in Spectrum Order
  * 6144 bytes colour attribute data in Spectrum Order
  * Optionally a ULAplus or ULANext extension

MLT: Timex Hi-Color screen dump (256x192)

  * 6144 bytes image data in Spectrum Order
  * 6144 bytes colour attribute data in left to right, top to bottom order
  * Optionally a ULAplus or ULANext extension

MC: Timex Hi-Color screen dump (256x192)

  * 6144 bytes image data in left to right, top to bottom order
  * 6144 bytes colour attribute data in left to right, top to bottom order
  * Optionally a ULAplus or ULANext extension

SHR: Timex Hi-Res screen dump (512x192)

  * 12288 bytes image data in Spectrum Order
  * Optional 1 byte hires colour pair
  * Oprional ULAplus extension

ULAplus extension:

  * 64 bytes of ULAplus palette information

ULANext extension:

  * 1 byte ULANext attribute ($01, $03, $07, $0F, $1F, $3F, $7F, or $FF)
  * 32 to 513 bytes of palette data depending on attribute value
    - Attribute $01: 130 or 260 bytes of palette data (2/128 colours)
    - Attribute $03: 68 or 136 bytes of palette data (4/64 colours)
    - Attribute $07: 40 or 80 bytes of palette data (8/32 colours)
    - Attribute $0F: 32 or 64 bytes of palette data (16/16 colours)
    - Attribute $1F: 40 or 80 bytes of palette data (32/8 colours)
    - Attribute $3F: 68 or 136 bytes of palette data (64/4 colors)
    - Attribute $7F: 130 or 260 bytes of palette data (128/2 colours)
    - Attribute $FF: 257 or 513 bytes of palette data (256/1 colours, paper colour is always 8-bit)

SL2: ZX Spectrum Next Layer 2 screen dump (256x192x8)

  * 49152 bytes of image data (left to right, top to bottom)
  * Optionally: 256 or 512 bytes of ZX Next palette data

SL2: ZX Spectrum Next Layer 2 screen dump (320x256x8)

  * 81920 bytes of image data (top to bottom, left to right)
  * Optionally: 256 or 512 bytes of ZX Next palette data

SL2: ZX Spectrum Next Layer 2 screen dump (640x256x4)

  * 81920 bytes of image data (each byte is a left to right pixel pair, bytes are arranged top to bottom, left to right)
  * Optionally: 16 or 32 bytes of ZX Next palette data

NXI: ZX Spectrum Next Layer 2 screen dump (256x192x8)

  * Optionally: 256 or 512 bytes palette data
  * 49152 bytes of image data

SLR: ZX Spectrum Next LoRes screen dump (128x96x8)

  * 12288 bytes of image data
  * Optionally: 256 or 512 bytes of palette data

SL2: Radastan Screen dump (128x96x4)

  * 6144 bytes of image data
  * Optionally: 16 or 32 bytes of palette data

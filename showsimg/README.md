# .showsimg: display ZX Next image formats.

Theodore (Alex) Evans 2020

Usage: .showsimg [&lt;options&gt;] &lt;filename&gt;\
options:\
  	-2: Layer 2 256x192x8\
  	-3: Layer 2 320x256x8\
  	-6: Layer 2 640x256x4\
  	-M: MLT HiCol\
  	-R: Radastan 128x96x4\
  	-S: Save state\
  	-c: Timex HiCol 256x192/8x1\
  	-h: Help\
  	-l: LoRes 128x96x8\
  	-m: MC HiCol\
	-n: NXI format (palette first)\
  	-r: Timex HiRes 512x192x1\
	-s: Restore state\
  	-u: ULA 256x192/8x8\
  	-x: Do not wait, do not restore\

With the -S and -s options an image filename is optional. It is useful
for writing slideshows in basic (see the test.bas example in the
test_images directory).

* Supports SCR, SHC, SHR, SL2, SLR, NXI, MC, and MLT files.
* SCR, SHC, and SHR support including ULAplus information.
* SHR files have an optional byte to choose the colour pair.
* All file formats support the addition of palette information.
* SCR and SHC files have an optional byte for the ULANext attribute.
* SL2 files can be 256x192x8, 320x256x8, or 640x256x4 (if there is no
palette, 640x256x4 files require a flag as they are identical in size
to 320x256x8).
* SLR files can be either Next style 128x96x8 or Radastan 128x96x4.

see FORMAT.md for extended format information.

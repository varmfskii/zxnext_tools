Tools for ZX Spectrum Next:

	- getpalette
	- img2asm
	- nexcreator
    - ppmtolayer2
    - ppmtolores

A note on programming philosophy and image formats.  These utilities
are written in the tradition of having programs that do one thing and
(try to) do it well. For this reason the idea is to have a lot of
small programs rather than a few big ones that can do everything. As
to image formats, there are a lot of image formats they have their
strengths and weaknesses. Since I have access to things like
ImageMagick and netpbm+, I see little reason to support a lot of image
formats directly. The choices I have made are pbm, pgm, and ppm (tying
directly to the ideas of netpbm+ which uses these formats as
intermediate formats). As a result most require the presence of
libnetpbm to compile/run.

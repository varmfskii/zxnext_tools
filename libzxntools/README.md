# libzxntools version 1.00.00 20190215

A set of library functions to support ZX Spectrum Next tools

## Types:

- ixed_t : an indexed representation of an image
- rgb_t : an rgba (8888) representation of an image
- rgba_t : an rgba pixel
- pal_t : an rgba palette
	
## Functions:

- int PAL3TO8(int)
- int PAL8TO3(int)
- int libzxntoolver(int)
- ixed_t readixed(FILE *, pal_t)
- ixed_t rgb2index(rgb_t, pal_t)
- pal_t palette(int)
- pal_t readpal(int, FILE *)
- rgb_t decimate(rgb_t, int, int, int, int)
- rgb_t readrgb(FILE *)
- void free_ixed(ixed_t)
- void free_pal(pal_t)
- void free_rgb(rgb_t)
- void writeixed(ixed_t, int, FILE *)
- void writepal(pal_t, FILE *)
- void writergb(rgb_t, FILE *)
- void nextpal(pal_t, FILE *)

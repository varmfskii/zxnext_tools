# libzxntools version 2.00.02 20200226

A set of library functions to support ZX Spectrum Next tools

## Types:

- bm_t : a black and white bitmap representation of an image
- ixed_t : an indexed representation of an image
- rgb_t : an rgba (8888) representation of an image
- rgba_t : an rgba pixel
- pal_t : an rgba palette
	
## Functions:

- bm_t new_bm(int, int);
- bm_t readbm(struct pam *);
- int PAL3TO8(int)
- int PAL8TO3(int)
- int col_dist(rgba_t, rgba_t);
- int col_distg(uint8_t, rgba_t);
- int get_verbose(void);
- int libzxntoolver(int)
- ixed_t new_ixed(int, int, int);
- ixed_t readixed(struct pam *, pal_t);
- ixed_t rgb2index(rgb_t, pal_t)
- pal_t new_pal(int);
- pal_t palette(int)
- pal_t readpal(int, FILE *)
- rgb_t decimate(rgb_t, int, int, int, int)
- rgb_t new_rgb(int, int, int);
- rgb_t readrgb(struct pam *);
- uint32_t plus3dos(uint8_t *);
- void free_bm(bm_t);
- void free_ixed(ixed_t)
- void free_pal(pal_t)
- void free_rgb(rgb_t)
- void nextpal(pal_t, FILE *)
- void set_verbose(int);
- void showpal(pal_t, FILE *);
- void writebm(bm_t, FILE *);
- void writeixed(ixed_t, int, FILE *)
- void writepal(pal_t, FILE *)
- void writeraw(ixed_t, width, height, depth, swap, FILE *)
- void writergb(rgb_t, FILE *)
- void writezxn(ixed_t, int, int, int, int, FILE *);

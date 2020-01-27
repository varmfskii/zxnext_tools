#ifndef ZXNTOOLS_H
#define ZXNTOOLS_H
#include <stdio.h>
#include <stdint.h>
#ifdef PAMPREFIX
#include <netpbm/pam.h>
#else
#include <pam.h>
#endif

typedef union rgba_t {
  uint32_t rgba;
  uint8_t p[4];
} rgba_t;

typedef struct rgb_t {
  int gray;
  union {
    rgba_t **dat;
    uint8_t **gdat;
  };
  int x,y;
} rgb_t;

typedef struct pal_t {
  rgba_t *dat;
  int l;
} pal_t;

typedef struct ixed_t {
  uint8_t **dat;
  pal_t pal;
  int x, y;
} ixed_t;

typedef struct bm_t {
  uint8_t **dat;
  int x, y;
} bm_t;

#define ZXNV 0x020001
#define ZXND "20200126"
#define R 0
#define G 1
#define B 2
#define A 3
#define PAL3TO8(X) ((((int) (X))*510+7)/14)
#define PAL8TO3(X) ((((int) (X))*14+255)/510)
#define ULACOLOURS \
  { 0xff000000, 0xffd70000, 0xff0000d7, 0xffd700d7, \
    0xff00d700, 0xffd7d700, 0xff00d7d7, 0xffd7d7d7, \
    0xff000000, 0xffff0000, 0xff0000ff, 0xffff00ff, \
    0xff00ff00, 0xffffff00, 0xff00ffff, 0xffffffff }    

bm_t new_bm(int x, int y);
bm_t readbm(struct pam *in);
int col_dist(rgba_t a, rgba_t b);
int col_distg(uint8_t a, rgba_t b);
int get_verbose(void);
int libzxntoolsver(int print);
ixed_t new_ixed(int x, int y, int d);
ixed_t readixed(struct pam *in, pal_t pal);
ixed_t rgb2index(rgb_t rgb, pal_t pal);
pal_t new_pal(int d);
pal_t palette(int n);
pal_t readpal(int len, FILE *palfile);
rgb_t decimate(rgb_t in, int xoff, int yoff, int xstep, int ystep);
rgb_t new_rgb(int x, int y, int gray);
rgb_t readrgb(struct pam *in);
void free_bm(bm_t i);
void free_ixed(ixed_t i);
void free_pal(pal_t p);
void free_rgb(rgb_t r);
void nextpal(pal_t pal, FILE *out);
void set_verbose(int);
void showpal(pal_t, FILE *out);
void writeixed(ixed_t v, int gray, FILE *out);
void writebm(bm_t bm, FILE *out);
void writepal(pal_t pal, FILE *out);
void writezxn(ixed_t ixed, int width, int height, int depth, int swap, FILE *out);
void writergb(rgb_t v, FILE *out);
#endif

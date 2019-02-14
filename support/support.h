#ifndef SUPPORT_H
#define SUPPORT_H
#include <stdio.h>
#include <stdint.h>

typedef union rgba_t {
  uint32_t rgba;
  uint8_t p[4];
} rgba_t;

typedef struct rgb_t {
  rgba_t **dat;
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

#define R 0
#define G 1
#define B 2
#define A 3
#define PAL3TO8(X) ((((int) (X))*510+7)/14)
#define PAL8TO3(X) ((((int) (X))*14+255)/510)

ixed_t readixed(FILE *in, pal_t pal);
ixed_t rgb2index(rgb_t rgb, pal_t pal);
pal_t palette(int n);
pal_t readpal(int len, FILE *palfile);
rgb_t decimate(rgb_t in, int xoff, int yoff, int xstep, int ystep);
rgb_t readrgb(FILE *in);
void free_ixed(ixed_t i);
void free_pal(pal_t p);
void free_rgb(rgb_t r);
void nextpal(pal_t pal, FILE *out);
void showpal(pal_t, FILE *out);
void writeixed(ixed_t v, int gray, FILE *out);
void writepal(pal_t pal, FILE *out);
void writergb(rgb_t v, FILE *out);

extern int verbose;
#endif

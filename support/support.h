#ifndef SUPPORT_H
#define SUPPORT_H
#include <stdio.h>

typedef struct rgb_t {
  unsigned char *dat;
  int x,y;
} rgb_t;

typedef struct pal_t {
  unsigned char *dat;
  int l;
} pal_t;

typedef struct ixed_t {
  unsigned char *dat;
  pal_t pal;
  int x, y;
} ixed_t;

pal_t readpal(int len, FILE *palfile);
pal_t palette(int n);
rgb_t readppm(FILE *in);
ixed_t rgb2index(rgb_t rgb, pal_t pal,
  int xoff, int yoff, int xstep, int ystep);
void showpal(pal_t);
#endif

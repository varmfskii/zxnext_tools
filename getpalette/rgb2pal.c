#include <stdlib.h>
#include "getpalette.h"

typedef struct pair {
  int color, count;
} pair;

int cmp(const void *, const void *);

pal_t rgb2pal(rgb_t rgb, int len) {
  pal_t pal;
  pair colors[512];
  int i, r, g, b;
  int ix, color;

  for(i=0; i<512; i++) colors[i].color=i;
  for(i=0; i<rgb.x*rgb.y*3; i+=3) {
    r=rgb.dat[i]*7/255;
    g=rgb.dat[i+1]*7/255;
    b=rgb.dat[i+2]*7/255;
    colors[(r<<6)|(g<<3)|b].count++;
  }
  qsort(colors, 512, sizeof(pair), cmp);
  pal.dat=(char *)malloc(3*len);
  for(i=0; i<len; i++) {
    ix=3*i;
    color=colors[i].color;
    pal.dat[ix]=((color>>6)&7)*255/7;
    pal.dat[ix+1]=((color>>3)&7)*255/7;
    pal.dat[ix+2]=(color&7)*255/7;
  }
  pal.l=len;
  return pal;
}

int cmp(const void *a, const void *b) {
  pair *x, *y;
  x=(pair *)a; y=(pair *)b;
  return x->count-y->count;
}

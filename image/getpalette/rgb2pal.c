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
  int color;

  for(i=0; i<512; i++) {
    colors[i].color=i;
    colors[i].count=0;
  }
  if (rgb.gray)
    for(i=0; i<rgb.x*rgb.y; i++) {
      g=PAL8TO3(rgb.gdat[0][i]);
      color=(g<<6)|(g<<3)|g;
      colors[color].count++;
    }
  else
    for(i=0; i<rgb.x*rgb.y; i++) {
      r=PAL8TO3(rgb.dat[0][i].p[R]);
      g=PAL8TO3(rgb.dat[0][i].p[G]);
      b=PAL8TO3(rgb.dat[0][i].p[B]);
      color=(r<<6)|(g<<3)|b;
      colors[color].count++;
    }
    
  qsort(colors, 512, sizeof(pair), cmp);
  pal.dat=(rgba_t *)calloc(len, sizeof(rgba_t));
  for(i=0; i<len; i++) {
    color=colors[i].color;
    pal.dat[i].p[R]=PAL3TO8((color>>6)&7);
    pal.dat[i].p[G]=PAL3TO8((color>>3)&7);
    pal.dat[i].p[B]=PAL3TO8(color&7);
    pal.dat[i].p[A]=0xff;
  }
  pal.l=len;
  return pal;
}

int cmp(const void *a, const void *b) {
  pair *x, *y;
  x=(pair *)a; y=(pair *)b;
  return (y->count)-(x->count);
}

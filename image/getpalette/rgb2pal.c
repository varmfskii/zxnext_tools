#include <stdlib.h>
#include "getpalette.h"

typedef struct pair {
  int color, count;
} pair;

int cmp(const void *, const void *);

pal_t rgb2pal(rgb_t rgb, int len) {
  pal_t pal;
  pair colors[512];
  int col_order[512];
  int i, r, g, b;
  int num_col;
  int color;

  for(i=0; i<512; i++) {
    colors[i].color=i;
    colors[i].count=0;
  }
  num_col=0;
  if (rgb.gray)
    for(i=0; i<rgb.x*rgb.y; i++) {
      g=PAL8TO3(rgb.gdat[0][i]);
      color=(g<<6)|(g<<3)|g;
      if (!colors[color].count) col_order[num_col++]=color;
      colors[color].count++;
    }
  else
    for(i=0; i<rgb.x*rgb.y; i++) {
      r=PAL8TO3(rgb.dat[0][i].p[R]);
      g=PAL8TO3(rgb.dat[0][i].p[G]);
      b=PAL8TO3(rgb.dat[0][i].p[B]);
      color=(r<<6)|(g<<3)|b;
      if (!colors[color].count) col_order[num_col++]=color;
      colors[color].count++;
    }
    
  pal.dat=(rgba_t *)calloc(len, sizeof(rgba_t));
  pal.l=len;
  if (num_col<=len) {
    /* return colors in order found */
    for(i=0; i<len; i++) {
      color=colors[col_order[i%num_col]].color;
      pal.dat[i].p[R]=PAL3TO8((color>>6)&7);
      pal.dat[i].p[G]=PAL3TO8((color>>3)&7);
      pal.dat[i].p[B]=PAL3TO8(color&7);
      pal.dat[i].p[A]=0xff;
    }
  } else {
    qsort(colors, 512, sizeof(pair), cmp);
    for(i=0; i<len; i++) {
      /* return most common colors in frequency order */
      color=colors[i].color;
      pal.dat[i].p[R]=PAL3TO8((color>>6)&7);
      pal.dat[i].p[G]=PAL3TO8((color>>3)&7);
      pal.dat[i].p[B]=PAL3TO8(color&7);
      pal.dat[i].p[A]=0xff;
    }
  }
  return pal;
}

int cmp(const void *a, const void *b) {
  pair *x, *y;
  x=(pair *)a; y=(pair *)b;
  return (y->count)-(x->count);
}

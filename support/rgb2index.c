#include <stdio.h>
#include <stdlib.h>
#include "support.h"

int col_dist(uint8_t *a, uint8_t *b);
int palix(uint8_t *color, pal_t pal);

/*
 * rgb2index(): convert an rgb image into an indexed image using a
 * given palette
 */

ixed_t rgb2index(rgb_t rgb, pal_t pal) {
  ixed_t ixed;
  int r, c;
  
  ixed.x=rgb.x;
  ixed.y=rgb.y;
  ixed.pal=pal;
  ixed.dat=(uint8_t **)malloc(ixed.y*sizeof(uint8_t *));
  ixed.dat[0]=(uint8_t *)malloc(ixed.x*ixed.y);
  for (r=0; r<ixed.y; r++) {
    ixed.dat[r]=ixed.dat[0]+ixed.x*r;
    for (c=0; c<ixed.x; c++) {
      ixed.dat[r][c]=palix(rgb.dat[r][c].p, pal);
    }
  }
  return ixed;
}

int palix(uint8_t *color, pal_t pal) {
  int i, ix;
  unsigned int min, dist;
  min=col_dist(color, pal.dat[0].p);
  ix=0;
  for(i=1; i<pal.l; i++) {
    dist=col_dist(color, pal.dat[i].p);
    if (dist<min) {
      min=dist;
      ix=i;
    }
  }
  return ix;
}

int col_dist(uint8_t *a, uint8_t *b) {
  int f, d;

  f=(int)a[0]-(int)b[0];
  d=f*f;
  f=(int)a[1]-(int)b[1];
  d+=f*f;
  f=(int)a[2]-(int)b[2];
  d+=f*f;
  return d;
}

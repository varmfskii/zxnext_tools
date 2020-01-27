#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zxntools.h"

int palix(rgba_t color, pal_t pal);
int palixg(uint8_t gray, pal_t pal);

/*
 * rgb2index(): convert an rgb image into an indexed image using a
 * given palette
 */

ixed_t rgb2index(rgb_t rgb, pal_t pal) {
  ixed_t ixed;
  int r, c;
  
  if (get_verbose()>1) fprintf(stderr, "rgb2index(rgb_t: %dx%d, pal_t: %d)\n",
		       rgb.x, rgb.y, pal.l);
  ixed=new_ixed(rgb.x, rgb.y, pal.l);
  memcpy(ixed.pal.dat, pal.dat, pal.l*sizeof(rgba_t));
  if (rgb.gray) {
      for (r=0; r<ixed.y; r++) {
        for (c=0; c<ixed.x; c++) {
	  ixed.dat[r][c]=(pal.l-1)*rgb.gdat[r][c]/255;
        }
      }
    /*
      for (r=0; r<ixed.y; r++) {
        for (c=0; c<ixed.x; c++) {
          ixed.dat[r][c]=palixg(rgb.gdat[r][c], pal);
        }
      }
    */
  } else
    for (r=0; r<ixed.y; r++) {
      for (c=0; c<ixed.x; c++) {
	ixed.dat[r][c]=palix(rgb.dat[r][c], pal);
      }
    }
  if (get_verbose()>1)
    fprintf(stderr, "return ixed_t: %dx%d\n", ixed.x, ixed.y);
  return ixed;
}

int palix(rgba_t color, pal_t pal) {
  int i, ix;
  unsigned int min, dist;
  min=col_dist(color, pal.dat[0]);
  ix=0;
  for(i=1; i<pal.l; i++) {
    dist=col_dist(color, pal.dat[i]);
    if (dist<min) {
      min=dist;
      ix=i;
    }
  }
  return ix;
}

int palixg(uint8_t gray, pal_t pal) {
  int i, ix;
  unsigned int min, dist;
  min=col_distg(gray, pal.dat[0]);
  ix=0;
  for(i=1; i<pal.l; i++) {
    dist=col_distg(gray, pal.dat[i]);
    if (dist<min) {
      min=dist;
      ix=i;
    }
  }
  return ix;
}

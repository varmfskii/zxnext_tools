#include <stdio.h>
#include <stdlib.h>
#include "img2asm.h"

inline int coldist(unsigned char *a, unsigned char *b);
int palix(unsigned char *color, unsigned char *pal, int palsz);

/*
 * rgb2index(): convert an rgb image into an indexed image using a
 * given palette
 */

ixed_t rgb2index(rgb_t rdat, pal_t pdat,
		int xoff, int yoff, int xstep, int ystep) {
  int ixx, ixy, ixsz, xsz, ysz, psz;
  int ixr, ixc, rgbr, rgbc;
  unsigned char *ix, *rgb, *pal;
  ixed_t rv;

  xsz=rdat.x;
  ysz=rdat.y;
  rgb=rdat.dat;
  pal=pdat.dat;
  psz=pdat.l;
  ixx=(xsz-xoff+xstep-1)/xstep;
  ixy=(ysz-yoff+ystep-1)/ystep;
  ixsz=ixx*ixy;
  ix=(unsigned char *)malloc(ixx*ixy);
  rgbr=3*xsz*yoff;
  for(ixr=0; ixr<ixsz; ixr+=ixx) {
    rgbc=3*xoff;
    for(ixc=0; ixc<ixx; ixc++) {
      ix[ixr+ixc]=palix(rgb+rgbr+rgbc, pal, psz);
      rgbc+=3;
    }
    rgbr+=3*xsz;
  }
  rv.dat=ix;
  rv.x=ixx;
  rv.y=ixy;
  rv.pal=pdat;
  return rv;
}

int palix(unsigned char *color, unsigned char *pal, int palsz) {
  int i, ix;
  unsigned int min, dist;
  min=coldist(color, pal);
  ix=0;
  for(i=1; i<palsz; i++) {
    dist=coldist(color, pal+3*i);
    if (dist<min) {
      min=dist;
      ix=i;
    }
  }
  return ix;
}

inline int coldist(unsigned char *a, unsigned char *b) {
  int f, d;

  f=(int)a[0]-(int)b[0];
  d=f*f;
  f=(int)a[1]-(int)b[1];
  d+=f*f;
  f=(int)a[2]-(int)b[2];
  d+=f*f;
  return d;
}

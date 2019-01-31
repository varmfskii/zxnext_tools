#include <stdio.h>
#include <stdlib.h>
#include "img2asm.h"

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
  //fprintf(stderr, "%dx%d\n", ixx, ixy);
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

  //fprintf(stderr, "%d %d %d\n", color[0], color[1], color[2]);
  min=(color[0]-pal[0])*(color[0]-pal[0]);
  min+=(color[1]-pal[1])*(color[1]-pal[1]);
  min+=(color[2]-pal[2])*(color[2]-pal[2]);
  //fprintf(stderr, "%d ", min);
  ix=0;
  for(i=1, pal+=3; i<palsz; i++, pal+=3) {
    dist=(color[0]-pal[0])*(color[0]-pal[0]);
    dist+=(color[1]-pal[1])*(color[1]-pal[1]);
    dist+=(color[2]-pal[2])*(color[2]-pal[2]);
    //fprintf(stderr, "%d ", dist);
    if (dist<min) {
      dist=min;
      ix=i;
    }
    pal+=3;
  }
  //fprintf(stderr, ": %d\n", min);
  return ix;
}

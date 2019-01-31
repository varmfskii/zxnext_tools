#include "img2asm.h"
#include <stdlib.h>
#include <pam.h>

/*
 * readimage(): read a ppm file returning an rgb image
 */

rgb_t readimage(FILE *in) {
  rgb_t rgb;
  struct pam inpam;
  char *argv[]={ "a.out", NULL };
  int ix, r, c, d, p, argc;
  tuple *tuplerow;

  argc=1;
  pnm_init(&argc, argv);
  pnm_readpaminit(in, &inpam, sizeof(inpam));
  tuplerow=pnm_allocpamrow(&inpam);
  rgb.x=inpam.width;
  rgb.y=inpam.height;
  rgb.dat=(char *)malloc(rgb.x*rgb.y*3);
  for(ix=r=0; r<rgb.y; r++) {
    pnm_readpamrow(&inpam, tuplerow);
    for(c=0; c<rgb.x; c++) {
      for(d=0; d<3; d++) {
        p=(inpam.depth==1)?0:d;
        rgb.dat[ix++]=255*tuplerow[c][p]/inpam.maxval;
      }
    }
  }
  pnm_freepamrow(tuplerow);
  return rgb;
}

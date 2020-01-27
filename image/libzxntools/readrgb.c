#include "zxntools.h"
#include <stdlib.h>

/*
 * readrgb(): read a ppm file returning an rgb image
 */

rgb_t readrgb(struct pam *inpam) {
  rgb_t rgb;
  int r, c, d;
  tuple *tuplerow;

  if (get_verbose()>1) fprintf(stderr, "readrgb(%p)\n", (void *)inpam);
  tuplerow=pnm_allocpamrow(inpam);
  if (inpam->depth==1) {
    /* pgm/pbm */
    rgb=new_rgb(inpam->width, inpam->height, inpam->maxval);
    for(r=0; r<rgb.y; r++) {
      pnm_readpamrow(inpam, tuplerow);
      for(c=0; c<rgb.x; c++)
	rgb.gdat[r][c]=255*tuplerow[c][1]/inpam->maxval;
    }
  } else {
    /* ppm */
    rgb=new_rgb(inpam->width, inpam->height, 0);
    for(r=0; r<rgb.y; r++) {
      pnm_readpamrow(inpam, tuplerow);
      for(c=0; c<rgb.x; c++) {
	for(d=0; d<3; d++) {
	  rgb.dat[r][c].p[d]=255*tuplerow[c][d]/inpam->maxval;
	}
	rgb.dat[r][c].p[3]=255;
      }
    }
  }
  pnm_freepamrow(tuplerow);
  if (get_verbose()>1) fprintf(stderr, "return rgb_t: %dx%d\n", rgb.x, rgb.y);
  return rgb;
}

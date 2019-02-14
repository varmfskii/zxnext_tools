#include "support.h"
#include <stdlib.h>
#include <pam.h>

/*
 * readrgb(): read a ppm file returning an rgb image
 */

rgb_t readrgb(FILE *in) {
  rgb_t rgb;
  struct pam inpam;
  char *argv[]={ "a.out", NULL };
  int r, c, d, p, argc;
  tuple *tuplerow;

  if (verbose) fprintf(stderr, "readrgb(%08llx)\n", (long long)in);
  argc=1;
  pnm_init(&argc, argv);
  pnm_readpaminit(in, &inpam, sizeof(inpam));
  tuplerow=pnm_allocpamrow(&inpam);
  rgb.x=inpam.width;
  rgb.y=inpam.height;
  rgb.dat=(rgba_t **)calloc(rgb.y, sizeof(rgba_t *));
  rgb.dat[0]=(rgba_t *)calloc(rgb.x*rgb.y, sizeof(rgba_t));
  for(r=0; r<rgb.y; r++) {
    rgb.dat[r]=rgb.dat[0]+r*rgb.x;
    pnm_readpamrow(&inpam, tuplerow);
    for(c=0; c<rgb.x; c++) {
      for(d=0; d<3; d++) {
        p=(inpam.depth==1)?0:d;
        rgb.dat[r][c].p[d]=255*tuplerow[c][p]/inpam.maxval;
      }
      rgb.dat[r][c].p[3]=255;
    }
  }
  pnm_freepamrow(tuplerow);
  return rgb;
}

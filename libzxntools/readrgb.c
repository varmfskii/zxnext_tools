#include "zxntools.h"
#include <stdlib.h>
#ifdef PREFIX
#include <netpbm/pam.h>
#else
#include <pam.h>
#endif

/*
 * readrgb(): read a ppm file returning an rgb image
 */

rgb_t readrgb(FILE *in) {
  rgb_t rgb;
  struct pam inpam;
  char *argv[]={ "a.out", NULL };
  int r, c, d, p, argc;
  tuple *tuplerow;

  if (verbose>1) fprintf(stderr, "readrgb(%p)\n", (void *)in);
  argc=1;
  pnm_init(&argc, argv);
  pnm_readpaminit(in, &inpam, sizeof(inpam));
  tuplerow=pnm_allocpamrow(&inpam);
  rgb=new_rgb(inpam.width, inpam.height);
  for(r=0; r<rgb.y; r++) {
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
  if (verbose>1) fprintf(stderr, "return rgb_t: %dx%d\n", rgb.x, rgb.y);
  return rgb;
}

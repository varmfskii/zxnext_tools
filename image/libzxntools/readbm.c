#include "zxntools.h"
#include <stdlib.h>
#ifdef PREFIX
#include <netpbm/pam.h>
#else
#include <pam.h>
#endif

/*
 * readbm(): read a ppm file returning a bit map (black and white) image
 */

bm_t readbm(FILE *in) {
  bm_t bm;
  struct pam inpam;
  char *argv[]={ "a.out", NULL };
  int r, c, cb, v, argc;
  tuple *tuplerow;

  if (verbose>1) fprintf(stderr, "readbm(%p)\n", (void *)in);
  argc=1;
  pnm_init(&argc, argv);
  pnm_readpaminit(in, &inpam, sizeof(inpam));
  tuplerow=pnm_allocpamrow(&inpam);
  bm=new_bm(inpam.width, inpam.height);
  for(r=0; r<bm.y; r++) {
    pnm_readpamrow(&inpam, tuplerow);
    for(cb=0; cb<bm.x; cb+=8) {
      v=0;
      for(c=0; c<8; c++) {
	if (!tuplerow[cb+c][0]) v|=0x80>>c;
      }
      bm.dat[r][cb/8]=v;
    }
  }
  pnm_freepamrow(tuplerow);
  if (verbose>1) fprintf(stderr, "return bm_t: %dx%d\n", bm.x, bm.y);
  return bm;
}

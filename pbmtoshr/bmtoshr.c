#include <stdio.h>
#include <stdlib.h>
#include "pbmtoshr.h"

void bmtoshr(bm_t bm, int dbl, FILE *out) {
  uint8_t left[0x1800], right[0x1800];
  int ar, ac, r, ix, m;

  m=dbl?2:1;
  if (bm.x<512 || bm.y<192*m) {
    fprintf(stderr, "Input image too small %dx%d\n", bm.x, bm.y);
    exit(1);
  }
  for(ar=0; ar<24; ar++)
    for(ac=0; ac<32; ac++)
      for(r=0; r<8; r++) {
	ix=(((ar&0x18)|r)<<8)|((ar&07)<<5)|ac;
	left[ix]=bm.dat[(ar*8+r)*m][ac*2];
	right[ix]=bm.dat[(ar*8+r)*m][ac*2+1];
      }
  fwrite(left, 1, 0x1800, out);
  fwrite(right, 1, 0x1800, out);
}

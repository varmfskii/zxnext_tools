#include <stdio.h>
#include <stdlib.h>
#include "shrtopbm.h"

bm_t shrtobm(FILE *in, int dbl) {
  bm_t rv;
  uint8_t left[0x1800], right[0x1800];
  int ar, ac, r, ix, m;

  m=dbl?2:1;
  if (fread(left, 1, 0x1800, in)!=0x1800 ||
      fread(right, 1, 0x1800, in)!=0x1800) {
    fprintf(stderr, "Input file too short\n");
    rv.x=rv.y=0;
    rv.dat=NULL;
    return rv;
  }
  rv=new_bm(512, 192*m);
  for(ar=0; ar<24; ar++)
    for(ac=0; ac<32; ac++) {
      for(r=0; r<8; r++) {
	ix=(((ar&0x18)|r)<<8)|((ar&07)<<5)|ac;
	rv.dat[(ar*8+r)*m][ac*2]=left[ix];
	rv.dat[(ar*8+r)*m][ac*2+1]=right[ix];
	if (dbl) {
	  rv.dat[(ar*8+r)*m+1][ac*2]=left[ix];
	  rv.dat[(ar*8+r)*m+1][ac*2+1]=right[ix];
	}
      }
    }
  return rv;
}

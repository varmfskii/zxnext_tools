#include <stdio.h>
#include <stdlib.h>
#include "shrtopbm.h"

bm_t shrtobm(FILE *in, int dbl) {
  bm_t rv;
  uint8_t data[0x3100], *buffer, *left, *right;
  int ar, ac, r, ix, m, size;

  m=dbl?2:1;
  buffer=data;
  size=fread(buffer, 1, 0x3100, in);
  if (plus3dos(buffer)) {
    buffer+=0x80;
    size-=0x80;
  }
  switch(size) {
  case 0x3000:
    left=buffer;
    right=buffer+0x1800;
    break;
  default:
    fprintf(stderr, "Input file invalid size\n");
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

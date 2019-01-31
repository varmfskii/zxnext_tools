#include <stdio.h>
#include "img2asm.h"

int writeraw(FILE *out, ixed_t idat, int txsz, int tysz) {
  int tr, tc, r, c, mask;
  int ix;
  int xsz, ysz, bits, b, v;
  char *dat;

  xsz=idat.x;
  ysz=idat.y;
  dat=idat.dat;
  switch(idat.pal.l) {
  case 2:
    bits=1;
    break;
  case 4:
    bits=2;
    break;
  case 16:
    bits=4;
    break;
  case 256:
    bits=8;
    break;
  default:
    fprintf(stderr, "Illegal bit depth\n");
    return -2;
  }
  if (xsz%txsz || ysz%tysz) {
    fprintf(stderr, "Not perfectly tilable\n");
    return -1;
  }
  mask=idat.pal.l-1;
  ix=0;
  for(tr=0; tr<ysz; tr+=tysz) {
    for(tc=0; tc<xsz; tc+=txsz) {
      for(r=0; r<tysz; r++) {
	ix=(tr+r)*xsz+tc;
	for(c=0; c<txsz; c+=(8/bits)) {
	  v=0;
	  for(b=0; b<8-bits; b+=bits)
	    v=(v<<bits)|(dat[ix++]&mask);
	  v=(v<<bits)|(dat[ix++]&mask);
	  putc(v, out);
	}
      }
    }
  }
  return 0;
}

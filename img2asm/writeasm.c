#include <stdio.h>
#include "img2asm.h"

int writeasm(FILE *out, ixed_t idat, int txsz, int tysz, char *label) {
  int tr, tc, r, c;
  int b, v, mask, cnt;
  int ix, rbase, col;
  int xsz, ysz, bits;
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
      return 1;
  }
  if (xsz%txsz || ysz%tysz) {
    fprintf(stderr, "Not perfectly tilable\n");
    return -1;
  }
  if (bits!=8 && bits!=4 && bits!=2 && bits !=1) {
    fprintf(stderr, "Illegal bit depth %d\n", bits);
    return -2;
  }
  fprintf(out, "%s:\n", label);
  mask=(1<<bits)-1;
  cnt=col=0;
  for(tr=0; tr<ysz; tr+=tysz) {
    for(tc=0; tc<xsz; tc+=txsz) {
      if (col) {
	putc('\n', out);
	col=0;
      }
      fprintf(out, ";; %s %02x\n", label, cnt++);
      for(r=0; r<tysz; r++) {
	rbase=(tr+r)*xsz;
	for(c=0; c<txsz; c+=(8/bits)) {
	  v=0;
	  ix=rbase+tc+c;
	  for(b=0; b<8-bits; b+=bits)
	    v=(v<<bits)|(dat[ix++]&mask);
	  v=(v<<bits)|(dat[ix]&mask);
	  if (col==0)
	    fprintf(out, "\tdefb $%02x", v);
	  else if (col!=15)
	    fprintf(out, ",$%02x", v);
	  else
	    fprintf(out, ",$%02x\n", v);
	  col=(col+1)%16;
	}
      }
    }
  }
  if (col) putc('\n', out);
  fprintf(out, "%s_end:\n", label);
  return 0;
}

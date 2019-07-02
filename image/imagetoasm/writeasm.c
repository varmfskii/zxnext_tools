#include <stdio.h>
#include "imagetoasm.h"

/*
 * writeasm(): write an assembly file (tiled) from an indexed image
 */

int writeasm(FILE *out, ixed_t idat, int txsz, int tysz, char *label) {
  int tr, tc, r, c, tx, ty;
  int b, v, mask, cnt, col;
  int rbase, cbase, bits;

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
  if (idat.x%txsz || idat.y%tysz) {
    fprintf(stderr, "Not perfectly tilable\n");
    return -1;
  }
  if (bits!=8 && bits!=4 && bits!=2 && bits !=1) {
    fprintf(stderr, "Illegal bit depth %d\n", bits);
    return -2;
  }
  tx=idat.x/txsz;
  ty=idat.y/tysz;
  mask=(1<<bits)-1;
  fprintf(out, "%s:\n", label);
  cnt=col=0;
  for(tr=0; tr<ty; tr++) {
    rbase=tr*tysz;
    for(tc=0; tc<tx; tc++) {
      cbase=tc*txsz;
      if (col) {
	putc('\n', out);
	col=0;
      }
      fprintf(out, ";; %s %02x\n", label, cnt++);
      for(r=0; r<tysz; r++) {
	for(c=0; c<txsz; c+=(8/bits)) {
	  v=0;
	  for(b=0; b<8/bits; b++)
	    v=(v<<bits)|(idat.dat[r+rbase][c+cbase+b]&mask);
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

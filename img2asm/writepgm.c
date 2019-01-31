#include <stdio.h>
#include "img2asm.h"

/*
 * writepgm(): write a pgm file (tiled) from an indexed image
 */

int writepgm(FILE *out, ixed_t idat, int txsz, int tysz) {
  int tr, tc, r, c, mask;
  int ix, ntiles;
  int xsz, ysz;
  char *dat;

  xsz=idat.x;
  ysz=idat.y;
  dat=idat.dat;
  if (xsz%txsz || ysz%tysz) {
    fprintf(stderr, "Not perfectly tilable\n");
    return -1;
  }
  ntiles=xsz/txsz*ysz/tysz;
  mask=idat.pal.l-1;
  fprintf(out, "P2\n%d %d\n%d\n", txsz, ntiles*tysz, mask);
  ix=0;
  for(tr=0; tr<ysz; tr+=tysz) {
    for(tc=0; tc<xsz; tc+=txsz) {
      for(r=0; r<tysz; r++) {
	ix=(tr+r)*xsz+tc;
	for(c=0; c<txsz-1; c++) {
	  fprintf(out, "%d ", dat[ix++]&mask);
	}
	fprintf(out, "%d\n", dat[ix++]&mask);
      }
    }
  }
  return 0;
}

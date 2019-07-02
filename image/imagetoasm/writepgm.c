#include <stdio.h>
#include "imagetoasm.h"

/*
 * writepgm(): write a pgm file (tiled) from an indexed image
 */

int writepgm(FILE *out, ixed_t idat, int txsz, int tysz) {
  int tr, tc, r, c, mask;
  int tx, ty, rbase, cbase;

  if (idat.x%txsz || idat.y%tysz) {
    fprintf(stderr, "Not perfectly tilable\n");
    return -1;
  }
  tx=idat.x/txsz;
  ty=idat.y/tysz;
  mask=idat.pal.l-1;
  fprintf(out, "P2\n%d %d\n%d\n", txsz, tx*ty*tysz, mask);
  for(tr=0; tr<ty; tr++) {
    rbase=tr*tysz;
    for(tc=0; tc<tx; tc++) {
      cbase=tc*txsz;
      for(r=0; r<tysz; r++) {
	for(c=0; c<txsz-1; c++) {
	  fprintf(out, "%d ", idat.dat[rbase+r][cbase+c]&mask);
	}
	fprintf(out, "%d\n", idat.dat[rbase+r][cbase+c]&mask);
      }
    }
  }
  return 0;
}

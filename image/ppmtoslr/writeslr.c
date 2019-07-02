#include <stdio.h>
#include "ppmtoslr.h"

void writeslr(ixed_t ixed, FILE *out) {
  int r;
  char zeros[0x80];
  
  if (verbose) fprintf(stderr, "writeslr(ixed_t: %dx%d, %p)\n",
		       ixed.x, ixed.y, (void *)out);
  for(r=0; r<96 && r<ixed.y; r++)
    if (ixed.x<0x80) {
      fwrite(ixed.dat[r], ixed.x, 1, out);
      fwrite(zeros, 0x80-ixed.x, 1, out);
    } else
      fwrite(ixed.dat[r], 0x80, 1, out);
  for(; r<96; r++)
    fwrite(zeros, 0x80, 1, out);
}

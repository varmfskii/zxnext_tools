#include <stdio.h>
#include "support.h"

void writergb(rgb_t rgb, FILE *out) {
  int r, c, d;

  fprintf(out, "P6\n%d %d\n255\n", rgb.x, rgb.y);
  for(r=0; r<rgb.y; r++)
    for(c=0; c<rgb.x; c++)
      for(d=0; d<3; d++) {
	putc(rgb.dat[r][c].p[d], out);
      }
}

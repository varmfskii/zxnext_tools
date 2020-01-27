#include <stdio.h>
#include "zxntools.h"

void writergb(rgb_t rgb, FILE *out) {
  int r, c, d;

  if (get_verbose()>1) fprintf(stderr, "writergb(rgb_t: %dx%d, %p)\n",
		       rgb.x, rgb.y, (void *) out);
  if (rgb.gray) {
    fprintf(out, "P5\n%d %d\n255\n", rgb.x, rgb.y);
    for(r=0; r<rgb.y; r++)
      for(c=0; c<rgb.x; c++)
	  putc(rgb.gdat[r][c], out);
  } else {
    fprintf(out, "P6\n%d %d\n255\n", rgb.x, rgb.y);
    for(r=0; r<rgb.y; r++)
      for(c=0; c<rgb.x; c++)
	for(d=0; d<3; d++) {
	  putc(rgb.dat[r][c].p[d], out);
	}
  }
}

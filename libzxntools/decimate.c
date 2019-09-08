#include <stdlib.h>
#include "zxntools.h"

rgb_t decimate(rgb_t in, int xoff, int yoff, int xstep, int ystep) {
  rgb_t out;
  int rout, rin, cout, cin;

  if (verbose>1) fprintf(stderr, "decimate(rgb_t: %dx%d, %d, %d, %d, %d)\n",
		       in.x, in.y, xoff, yoff, xstep, ystep);
  out=new_rgb((in.x+xstep-xoff-1)/xstep, (in.y+ystep-yoff-1)/ystep);
  for(rout=0, rin=yoff; rout<out.y; rout++, rin+=ystep) {
    for(cout=0, cin=xoff; cout<out.x; cout++, cin+=xstep) {
      out.dat[rout][cout].rgba=in.dat[rin][cin].rgba;
    }
  }
  if (verbose>1) fprintf(stderr, "return rgb_t: %dx%d\n", out.x, out.y);
  return out;
}

#include <stdlib.h>
#include "support.h"

rgb_t decimate(rgb_t in, int xoff, int yoff, int xstep, int ystep) {
  rgb_t out;
  int rout, rin, cout, cin;

  if (verbose) fprintf(stderr, "decimate(in, %d, %d, %d, %d)\n",
		       xoff, yoff, xstep, ystep);
  out.x=(in.x+xstep-xoff-1)/xstep;
  out.y=(in.y+ystep-yoff-1)/ystep;
  out.dat=(rgba_t **)calloc(out.y, sizeof(rgba_t *));
  out.dat[0]=(rgba_t *)calloc(out.x*out.y, sizeof(rgba_t));
  for(rout=0, rin=yoff; rout<out.y; rout++, rin+=ystep) {
    out.dat[rout]=out.dat[0]+rout*out.x;
    for(cout=0, cin=xoff; cout<out.x; cout++, cin+=xstep) {
      out.dat[rout][cout].rgba=in.dat[rin][cin].rgba;
    }
  }
  return out;
}

#include <stdio.h>
#include <stdlib.h>
#include "zxntools.h"

ixed_t readixed(FILE *in, pal_t pal) {
  ixed_t out;
  rgb_t rgb;

  if (verbose>1)
    fprintf(stderr, "readixed(%p, pal_t: %d)\n", (void *) in, pal.l);
  rgb=readrgb(in);
  out=rgb2index(rgb, pal);
  free_rgb(rgb);
  if (verbose>1) fprintf(stderr, "return ixed_t: %dx%d\n", out.x, out.y);
  return out;
}

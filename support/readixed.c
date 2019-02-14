#include <stdio.h>
#include <stdlib.h>
#include "support.h"

ixed_t readixed(FILE *in, pal_t pal) {
  ixed_t out;
  rgb_t rgb;

  if (verbose) fprintf(stderr, "readixed(%08llx, %d)\n", (long long) in, pal.l);
  rgb=readrgb(in);
  out=rgb2index(rgb, pal);
  free(rgb.dat[0]);
  free(rgb.dat);
  return out;
}

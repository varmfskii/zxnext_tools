#include <stdlib.h>
#include "zxntools.h"

void free_ixed(ixed_t i) {
  if (verbose) fprintf(stderr, "free_ixed(ixed_t: %dx%d)\n", i.x, i.y);
  free(i.dat[0]);
  free(i.dat);
  i.dat=NULL;
  i.x=0;
  i.y=0;
  free_pal(i.pal);
}

void free_pal(pal_t p) {
  if (verbose) fprintf(stderr, "free_pal(pal_t: %d)\n", p.l);
  free(p.dat);
  p.dat=NULL;
  p.l=0;
}

void free_rgb(rgb_t r) {
  if (verbose) fprintf(stderr, "free_rgb(rgb_t: %dx%d)\n", r.x, r.y);
  free(r.dat[0]);
  free(r.dat);
  r.dat=NULL;
  r.x=0;
  r.y=0;
}

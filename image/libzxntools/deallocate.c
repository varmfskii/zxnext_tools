#include <stdlib.h>
#include "zxntools.h"

void free_ixed(ixed_t i) {
  if (get_verbose()>1) fprintf(stderr, "free_ixed(ixed_t: %dx%d)\n", i.x, i.y);
  if (i.dat) {
    free(i.dat);
    i.dat=NULL;
  }
  i.x=0;
  i.y=0;
  free_pal(i.pal);
}

void free_pal(pal_t p) {
  if (get_verbose()>1) fprintf(stderr, "free_pal(pal_t: %d)\n", p.l);
  if (p.dat) {
    free(p.dat);
    p.dat=NULL;
  }
  p.l=0;
}

void free_rgb(rgb_t r) {
  if (get_verbose()>1) fprintf(stderr, "free_rgb(rgb_t: %dx%d)\n", r.x, r.y);
  if (r.gray && r.gdat) {
    free(r.gdat);
    r.gdat=NULL;
  } else if (!r.gray && r.dat) {
    free(r.dat);
    r.dat=NULL;
  }
  r.x=0;
  r.y=0;
}

void free_bm(bm_t r) {
  if (get_verbose()>1) fprintf(stderr, "free_bm(bm_t: %dx%d)\n", r.x, r.y);
  if (r.dat) {
    free(r.dat);
    r.dat=NULL;
  }
  r.x=0;
  r.y=0;
}

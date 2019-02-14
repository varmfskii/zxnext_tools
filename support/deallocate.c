#include <stdlib.h>
#include "support.h"

void free_ixed(ixed_t i) {
  free(i.dat[0]);
  free(i.dat);
  i.dat=NULL;
  i.x=0;
  i.y=0;
  free_pal(i.pal);
}

void free_pal(pal_t p) {
  free(p.dat);
  p.dat=NULL;
  p.l=0;
}

void free_rgb(rgb_t r) {
  free(r.dat[0]);
  free(r.dat);
  r.dat=NULL;
  r.x=0;
  r.y=0;
}

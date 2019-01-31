#include "getpalette.h"
#include <stdio.h>

void writepal(pal_t pal, FILE *out) {
  int i;

  for(i=0; i<3*pal.l; i++) putc(pal.dat[i], out);
}

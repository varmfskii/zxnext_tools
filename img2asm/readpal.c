#include "img2asm.h"
#include <stdlib.h>

pal_t readpal(int len, FILE *in) {
  pal_t pal;
  int i, c;

  pal.dat=calloc(1, 3*len);
  for(i=0; i<3*len; i++) {
    if ((c=getc(in))==EOF) break;
    pal.dat[i]=c;
  }
  pal.l=len;
  return pal;
}

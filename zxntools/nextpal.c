#include <stdio.h>
#include "zxntools.h"

void nextpal(pal_t pal, FILE *out) {
  int i, c, v;

  for(i=0; i<256 && i<pal.l; i++) {
    for(v=c=0; c<3; c++)
      v=(v<<3)|PAL8TO3(pal.dat[i].p[c]);
    putc(v>>1, out);
    putc((v&0x100)?1:0, out);
  }
  for(; i<256; i++) {
    putc(0, out);
    putc(0, out);
  }
}

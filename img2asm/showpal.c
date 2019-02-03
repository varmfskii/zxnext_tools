#include <stdio.h>
#include "img2asm.h"

void showpal(pal_t pal) {
  int i;
  
  for(i=0; i<pal.l; i++) {
    fprintf(stderr, "%d: %d %d %d\n", i, pal.dat[3*i],
	    pal.dat[3*i+1], pal.dat[3*i+2]);
  }
}

#include <stdio.h>
#include "ppmtosl2.h"

void writesl2(ixed_t ixed, FILE *out) {
  int r;
  char zeros[0x100];
  
  for(r=0; r<192 && r<ixed.y; r++)
    if (ixed.x<0x100) {
      fwrite(ixed.dat[r], ixed.x, 1, out);
      fwrite(zeros, 0x100-ixed.x, 1, out);
    } else
      fwrite(ixed.dat[r], 0x100, 1, out);
  for(; r<192; r++)
    fwrite(zeros, 0x100, 1, out);
}

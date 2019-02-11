#include <stdio.h>
#include "ppmtolores.h"

void writelores(ixed_t ixed, FILE *out) {
  int r;
  char zeros[0x80];
  
  for(r=0; r<0x60 && r<ixed.y; r++)
    if (ixed.x<0x80) {
      fwrite(ixed.dat+ixed.y*r, ixed.x, 1, out);
      fwrite(zeros, 0x80-ixed.x, 1, out);
    } else
      fwrite(ixed.dat+ixed.y*r, 0x80, 1, out);
  for(; r<0x60; r++)
    fwrite(zeros, 0x80, 1, out);
}

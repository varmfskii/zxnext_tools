#include <stdio.h>
#include <stdlib.h>
#include "img2asm.h"

#define X 32
#define Y 32

int main() {
  pal_t pal;
  rgb_t rgb;
  ixed_t ixed;

  pal=palette(4);
  rgb.dat=(char *)calloc(X*Y,3);
  rgb.x=X;
  rgb.y=Y;
  for(int i=0; i<32*32*3; i++) rgb.dat[i]=rand()&0xff;
  ixed=rgb2index(rgb, pal, 0, 0, 1, 1);
  free(rgb.dat);
  for(int r=0; r<ixed.y; r++) {
    for(int c=0; c<ixed.x; c++) {
      printf("%x", ixed.dat[r*ixed.x+c]);
    }
    putchar('\n');
  }
  writeasm(stdout, ixed, 8, 8, "tile");
  ixed.pal.l=256;
  writeasm(stdout, ixed, 16, 16, "sprite");
  free(ixed.pal.dat);
  free(ixed.dat);
  return 0;
}

#include <stdio.h>
#include "zxntools.h"

void writezxn(ixed_t ixed, int width, int height,
	      int depth, int swap, FILE *out) {
  /* Assumes depth is 1, 2, 4, or 8
   swap = swap x and y axes */
  int r, c, sc, bits, byte, ppb;

  if (get_verbose()>1)
    fprintf(stderr, "writezxn(ixed_t: %dx%d, width: %d, height: %d, "
	    "depth: %d, swap: %d, out: %p)\n",
	    ixed.x, ixed.y, width, height, depth, swap, (void *) out);
  ppb=8/depth;
  if (width%ppb) {
    fputs("Row does not contain a whole number of bytes\n", stderr);
    return;
  }
  if (swap) {
    for(c=0; c<ixed.x && c<width; c+=ppb) {
      for(r=0; r<ixed.y && r<height; r++) {
	for(byte=sc=0; sc<ppb; sc++) byte=(byte<<depth)|ixed.dat[r][c+sc];
	putc(byte, out);
      }
      for(; r<height; r++) putc('\0', out);
    }
    for(; c<width; c+=ppb)
      for(r=0; r<height; r++) putc('\0', out);
  } else {
    for(r=0; r<ixed.y && r<height; r++) {
      for(c=0; c<ixed.x && c<width; c+=ppb) {
	for(byte=sc=0; sc<ppb; sc++) byte=(byte<<depth)|ixed.dat[r][c+sc];
	putc(byte, out);
      }
      for(; c<width; c+=ppb) putc('\0', out);
    }
    for(; r<height; r++)
      for(c=0; c<width; c+=ppb) putc('\0', out);
  }      
}

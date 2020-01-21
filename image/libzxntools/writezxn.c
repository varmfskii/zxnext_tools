#include <stdio.h>
#include "zxntools.h"

void writezxn(ixed_t ixed, int width, int height,
	      int depth, int swap, FILE *out) {
  /* Assumes depth is 1, 2, 4, or 8
   swap = swap x and y axes */
  int r, c, ix, bits, byte;
  unsigned char buffer[width*height];

  if (verbose>1)
    fprintf(stderr, "writezxn(ixed_t: %dx%d, width: %d, height: %d, "
	    "depth: %d, swap: %d, out: %p)\n",
	    ixed.x, ixed.y, width, height, depth, swap, (void *) out);
  if (swap) {
    if ((depth*height)%8) {
      fputs("Column does not contain a whole number of bytes\n", stderr);
      return;
    }
    ix=0;
    for(c=0; c<ixed.x && c<width; c++) {
      for(r=0; r<ixed.y && r<height; r++) buffer[ix++]=ixed.dat[r][c];
      for(; r<height; r++) buffer[ix++]='\0';
    }
    for(; c<width; c++)
      for(r=0; r<height; r++) buffer[ix++]='\0';
  } else {
    if ((depth*width)%8) {
      fputs("Row does not contain a whole number of bytes\n", stderr);
      return;
    }
    ix=0;
    for(r=0; r<ixed.y && r<height; r++) {
      for(c=0; c<ixed.x && c<width; c++) buffer[ix++]=ixed.dat[r][c];
      for(; c<width; c++) buffer[ix++]='\0';
    }
    for(; r<height; r++)
      for(c=0; c<width; c++) buffer[ix++]='\0';
  }      
  if (depth==8) {
    fwrite(buffer, 1, width*height, out);
    return;
  }
  bits=byte=0;
  for(ix=0; ix<width*height; ix++) {
    if (verbose>2) fprintf(stderr, "bits: %d\n", bits);
    byte=(byte<<depth)|buffer[ix];
    bits+=depth;
    if (bits>=8) {
      putc(byte, out);
      bits=byte=0;
    }
  }
}

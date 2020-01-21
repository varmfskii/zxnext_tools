#include <stdio.h>
#include <stdlib.h>
#include "shctoppm.h"

uint32_t ulacolor[]=ULACOLOURS;

rgb_t shctorgb(FILE *in) {
  rgb_t rv;
  uint8_t pixel[0x1800], attr[0x1800];
  int ar, ac, r, c;
  int ix, a, ink, paper;

  if (fread(pixel, 1, 0x1800, in)!=0x1800 ||
      fread(attr, 1, 0x1800, in)!=0x1800) {
    fprintf(stderr, "Input file too short\n");
    rv.x=rv.y=0;
    rv.dat=NULL;
    return rv;
  }
  rv=new_rgb(256, 192, 0);
  for(ar=0; ar<24; ar++)
    for(ac=0; ac<32; ac++) {
      for(r=0; r<8; r++) {
	ix=(((ar&0x18)|r)<<8)|((ar&07)<<5)|ac;
	a=attr[ix];
	paper=ulacolor[(a>>3)&0x0f];
	ink=ulacolor[(a&0x07)|((a>>3)&0x08)];
	for(c=0; c<8; c++) {
	  rv.dat[ar*8+r][ac*8+c].rgba=(pixel[ix]&(0x80>>c))?ink:paper;
	}
      }
    }
  return rv;
}

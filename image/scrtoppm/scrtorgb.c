#include <stdio.h>
#include <stdlib.h>
#include "scrtoppm.h"

uint32_t ulacolor[]=ULACOLOURS;

rgb_t scrtorgb(FILE *in) {
  rgb_t rv;
  uint8_t data[0x1c00], *buffer;
  uint8_t *pixel, *attr;
  int ar, ac, r, c;
  int ix, a, ink, paper, size;

  buffer=data;
  size=fread(buffer, 1, 0x1c00, in);
  if(plus3dos(buffer)) {
    buffer+=0x80;
    size-=0x80;
    fprintf(stderr, "+3dos header\n");
  }
  switch(size) {
  case 0x1b00:
    pixel=buffer;
    attr=buffer+0x1800;
    break;
  default:
    fprintf(stderr, "Input file invalid size\n");
    rv.x=rv.y=0;
    rv.dat=NULL;
    return rv;
  }
  rv=new_rgb(256, 192, 0);
  for(ar=0; ar<24; ar++)
    for(ac=0; ac<32; ac++) {
      a=attr[ar*32+ac];
      paper=ulacolor[(a>>3)&0x0f];
      ink=ulacolor[(a&0x07)|((a>>3)&0x08)];
      for(r=0; r<8; r++) {
	ix=(((ar&0x18)|r)<<8)|((ar&07)<<5)|ac;
	for(c=0; c<8; c++) {
	  rv.dat[ar*8+r][ac*8+c].rgba=(pixel[ix]&(0x80>>c))?ink:paper;
	}
      }
    }
  return rv;
}

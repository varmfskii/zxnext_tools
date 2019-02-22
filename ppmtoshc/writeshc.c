#include <stdio.h>
#include "ppmtoshc.h"

void writeshc(ixed_t ixed, FILE *out) {
  uint8_t pixels[0x1800], attr[0x1800];
  int ac, ar, c, r, ix, v;
  int cc[16], p, i, pc, ic;
  rgba_t ink, paper;

  for(ar=0; ar<24; ar++) {
    for(ac=0; ac<32; ac++) {
      for(r=0; r<8; r++) {
	/* find best ink and paper colors */
	for(ix=0; ix<16; ix++) cc[ix]=0;
	for(c=0; c<8; c++)
	  cc[ixed.dat[ar*8+r][ac*8+c]]++;
	p=15; i=8; pc=0; ic=0;
	for(ix=0; ix<16; ix++)
	  if (cc[ix]>pc) {
	    ic=pc; pc=cc[ix];
	    i=p; p=ix;
	  } else if (cc[ix]>ic) {
	    ic=cc[ix];
	    i=ix;
	  }
	/* if either is bright, both are bright */
	p=p|(i&8);
	i=i|(p&8);
	/* set attribute */
	ix=(((ar&0x18)|r)<<8)|((ar&07)<<5)|ac;
	attr[ix]=(p<<3)|(i&7);
	paper.rgba=ixed.pal.dat[p].rgba;
	ink.rgba=ixed.pal.dat[i].rgba;
	/* find and set whether ink or paper */
	v=0;
	for(c=0; c<8; c++) {
	  if (col_dist(ixed.pal.dat[ixed.dat[ar*8+r][ac*8+c]], ink)<
	      col_dist(ixed.pal.dat[ixed.dat[ar*8+r][ac*8+c]], paper))
	    v|=0x80>>c;
	}
	pixels[ix]=v;
      }
    }
  }
  fwrite(pixels, 1, 0x1800, out);
  fwrite(attr, 1, 0x1800, out);
}

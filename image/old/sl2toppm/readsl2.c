#include <stdlib.h>
#include <string.h>
#include "sl2toppm.h"

ixed_t readsl2(FILE *in) {
  int size, i;
  uint8_t buffer[0xc200];
  ixed_t rv;
  pal_t pal;
  
  rv.x=0;
  rv.y=0;
  pal.l=0;
  pal.dat=NULL;
  rv.pal=pal;
  rv.dat=NULL;
  size=fread(buffer, 1, sizeof(buffer), in);
  switch(size) {
  case 0xc000:
    pal=palette(8);
    break;
  case 0xc100:
    pal.dat=calloc(0x100, sizeof(rgba_t));
    for(i=0; i<0x100; i++) {
      pal.dat[i].p[R]=PAL3TO8((buffer[0xc000+i]>>5)&7);
      pal.dat[i].p[G]=PAL3TO8((buffer[0xc000+i]>>2)&7);
      pal.dat[i].p[B]=(buffer[0xc000+i]&3)/85;
      pal.dat[i].p[A]=0xff;
    }
    break;
  case 0xc200:
    pal.dat=calloc(0x100, sizeof(rgba_t));
    for(i=0; i<0x100; i++) {
      pal.dat[i].p[R]=PAL3TO8((buffer[0xc000+2*i]>>5)&7);
      pal.dat[i].p[G]=PAL3TO8((buffer[0xc000+2*i]>>2)&7);
      pal.dat[i].p[B]=PAL3TO8(((buffer[0xc000+2*i]&3)<<1)|
			      (buffer[0xc001+2*i]&1));
      pal.dat[i].p[A]=0xff;
    }
    break;
  default:
    fprintf(stderr, "Invalid file size\n");
    return rv;
  }
  rv.x=256;
  rv.y=192;
  rv.pal=pal;
  rv.dat=calloc(192, sizeof(uint8_t *));
  rv.dat[0]=malloc(0xc000);
  memcpy(rv.dat[0], buffer, 0xc000);
  for(i=1; i<192; i++) rv.dat[i]=rv.dat[0]+0x100*i;
  return rv;
}

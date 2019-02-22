#include <stdlib.h>
#include <string.h>
#include "slrtoppm.h"

ixed_t readslr(FILE *in) {
  int size, i;
  uint8_t buffer[0x3200];
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
  case 0x3000:
    pal=palette(8);
    break;
  case 0x3100:
    pal.dat=calloc(0x100, sizeof(rgba_t));
    for(i=0; i<0x100; i++) {
      pal.dat[i].p[R]=PAL3TO8((buffer[0x3000+i]>>5)&7);
      pal.dat[i].p[G]=PAL3TO8((buffer[0x3000+i]>>2)&7);
      pal.dat[i].p[B]=(buffer[0x3000+i]&3)/85;
      pal.dat[i].p[A]=0xff;
    }
    break;
  case 0x3200:
    pal.dat=calloc(0x100, sizeof(rgba_t));
    for(i=0; i<0x100; i++) {
      pal.dat[i].p[R]=PAL3TO8((buffer[0x3000+2*i]>>5)&7);
      pal.dat[i].p[G]=PAL3TO8((buffer[0x3000+2*i]>>2)&7);
      pal.dat[i].p[B]=PAL3TO8(((buffer[0x3000+2*i]&3)<<1)|
			      (buffer[0x3001+2*i]&1));
      pal.dat[i].p[A]=0xff;
    }
    break;
  default:
    fprintf(stderr, "Invalid file size\n");
    return rv;
  }
  rv.x=128;
  rv.y=96;
  rv.pal=pal;
  rv.dat=calloc(96, sizeof(uint8_t *));
  rv.dat[0]=malloc(0x3000);
  memcpy(rv.dat[0], buffer, 0x3000);
  for(i=1; i<96; i++) rv.dat[i]=rv.dat[0]+0x80*i;
  return rv;
}

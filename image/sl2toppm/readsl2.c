#include <stdlib.h>
#include <string.h>
#include "sl2toppm.h"

ixed_t readsl2(FILE *in) {
  int size, i, j, offset, palsz;
  uint8_t space[0x14200], *buffer;
  ixed_t rv;
  pal_t pal;
  
  rv.x=0;
  rv.y=0;
  pal.l=0;
  pal.dat=NULL;
  rv.pal=pal;
  rv.dat=NULL;
  buffer=space;
  size=fread(buffer, 1, sizeof(space), in);
  if (get_verbose()) fprintf(stderr, "read size %x\n", size);
  if (plus3dos(buffer)) {
    size-=0x80;
    buffer=buffer+0x80;
  }
  palsz=size&0x3ff;
  switch(size) {
  case 0x1800:
    /* radistan */
  case 0x1810:
    /* radistan w/ palette 1 */
  case 0x1820:
    /* radistan w/ palette 2 */
    rv.x=128;
    rv.y=96;
    offset=0x1800;
    break;
  case 0x3000:
    /* lores */
  case 0x3100:
    /* lores w/ palette 1 */
  case 0x3200:
    /* lores w/ palette 2 */
    rv.x=128;
    rv.y=96;
    offset=0x3000;
    break;
  case 0xc000:
    /* layer 2 256x192 */
  case 0xc100:
    /* layer 2 256x192 w/ palette 1 */
  case 0xc200:
    /* layer 2 256x192 w/ palette 2 */
    rv.x=256;
    rv.y=192;
    offset=0xc000;
    break;
  case 0x14000:
    /* layer 2 320x256 */
    /* layer 2 640x256 */
  case 0x14010:
    /* layer 2 640x256 w/ palette 1 */
  case 0x14020:
    /* layer 2 640x256 w/ palette 2 */
  case 0x14100:
    /* layer 2 320x256 w/ palette 1 */
  case 0x14200:
    /* layer 2 320x256 w/ palette 2 */
    if (palsz==0x10 || palsz==0x20)
      rv.x=640;
    else if (palsz==0x100 || palsz==0x200)
      rv.x=320;
    else
      rv.x=pref;
    rv.y=256;
    offset=0x14000;
    break;
  default:
    fprintf(stderr, "Invalid file size\n");
    rv.x=0;
    rv.y=0;
    return rv;
  }
  switch(palsz) {
  case 0x000:
    if (rv.x==640 || offset==0x1800) {
      pal=palette(4);
    } else {
      pal=palette(8);
    }
    break;
  case 0x010:
    pal.dat=calloc(0x010, sizeof(rgba_t));
    for(i=0; i<0x010; i++) {
      pal.dat[i].p[R]=PAL3TO8((buffer[offset+i]>>5)&7);
      pal.dat[i].p[G]=PAL3TO8((buffer[offset+i]>>2)&7);
      pal.dat[i].p[B]=(buffer[offset+i]&3)*85;
      pal.dat[i].p[A]=0xff;
    }
    break;
  case 0x020:
    pal.dat=calloc(0x010, sizeof(rgba_t));
    for(i=0; i<0x010; i++) {
      pal.dat[i].p[R]=PAL3TO8((buffer[offset+2*i]>>5)&7);
      pal.dat[i].p[G]=PAL3TO8((buffer[offset+2*i]>>2)&7);
      pal.dat[i].p[B]=PAL3TO8(((buffer[offset+2*i]<<1)&6)
			      |(buffer[offset+2*i+1]&1));
      pal.dat[i].p[A]=0xff;
    }
    break;
  case 0x100:
    pal.dat=calloc(0x100, sizeof(rgba_t));
    for(i=0; i<0x100; i++) {
      pal.dat[i].p[R]=PAL3TO8((buffer[offset+i]>>5)&7);
      pal.dat[i].p[G]=PAL3TO8((buffer[offset+i]>>2)&7);
      pal.dat[i].p[B]=(buffer[offset+i]&3)*85;
      pal.dat[i].p[A]=0xff;
    }
    break;
  case 0x200:
    pal.dat=calloc(0x100, sizeof(rgba_t));
    for(i=0; i<0x100; i++) {
      pal.dat[i].p[R]=PAL3TO8((buffer[offset+2*i]>>5)&7);
      pal.dat[i].p[G]=PAL3TO8((buffer[offset+2*i]>>2)&7);
      pal.dat[i].p[B]=PAL3TO8(((buffer[offset+2*i]&3)<<1)|
			      (buffer[offset+1+2*i]&1));
      pal.dat[i].p[A]=0xff;
    }
    break;
  }
  rv.pal=pal;
  rv.dat=calloc(rv.y, sizeof(uint8_t *));
  rv.dat[0]=malloc(rv.x*rv.y);
  for(i=1; i<rv.y; i++) rv.dat[i]=rv.dat[0]+rv.x*i;
  if (rv.y==192 || (rv.y==96 && offset==0x3000)) {
    memcpy(rv.dat[0], buffer, rv.x*rv.y);
  } else if (rv.x==320) {
    for(i=0; i<320; i++)
      for(j=0; j<256; j++) rv.dat[j][i]=buffer[256*i+j];
  } else if (rv.x==640) {
    for(i=0; i<640; i++)
      for(j=0; j<128; j++) {
	rv.dat[2*j][i]=buffer[128*i+j]>>4;
	rv.dat[2*j+1][i]=buffer[128*i+j]&0x0f;
      }
  } else {
    for(i=0; i<64; i++)
      for(j=0; j<96; j++) {
	rv.dat[j][2*i]=buffer[64*j+i]>>4;
	rv.dat[j][2*i+1]=buffer[64*j+i]&0x0f;
      }
  }
  return rv;
}

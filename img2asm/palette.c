#include <stdlib.h>
#include <string.h>
#include "img2asm.h"

pal_t palette(int n) {
  int i, ix;
  pal_t rv;
  char v3to8[]={0, 36, 73, 109, 146, 182, 219, 255};
  char v2to8[]={0, 109, 182, 255};
  char pal1[]={
    0, 0, 0,
    255, 255, 255
  };
  char pal2[]={
    0, 0, 0,
    255, 0, 0,
    0, 255, 255,
    255, 255, 255
  };
  char pal4[]={
    0, 0, 0,
    109, 0, 0,
    0, 109, 0,
    109, 109, 0,
    0, 0, 109,
    109, 0, 109,
    0, 109, 109,
    182, 182, 182,
    73, 73, 73,
    255, 0, 0,
    0, 255, 0,
    255, 255, 0,
    0, 0, 255,
    255, 0, 255,
    0, 255, 255,
    255, 255, 255
  };

  switch (n) {
    case 1:
      rv.dat=(char *)malloc(6);
      memcpy(rv.dat, pal1, 6);
      rv.l=2;
      return rv;
    case 2:
      rv.dat=(char *)malloc(12);
      memcpy(rv.dat, pal2, 12);
      rv.l=4;
      return rv;
    case 4:
      rv.dat=(char *)malloc(48);
      memcpy(rv.dat, pal4, 48);
      rv.l=16;
      return rv;
    case 8:
      rv.dat=(char *)malloc(768);
      for(ix=i=0; i<256; i++) {
          rv.dat[ix++]=v3to8[(i>>5)&7];
          rv.dat[ix++]=v3to8[(i>>2)&7];
          rv.dat[ix++]=v2to8[i&3];
      }
      rv.l=256;
      return rv;
  }
  rv.dat=NULL;
  rv.l=0;
  return rv;
}

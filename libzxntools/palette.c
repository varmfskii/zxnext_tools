#include <stdlib.h>
#include <string.h>
#include "zxntools.h"

/*
 * palette(): generate a palette of a given size
 */

pal_t palette(int n) {
  int i;
  pal_t rv;
  static uint8_t v3to8[]={0, 36, 73, 109, 146, 182, 219, 255};
  static uint8_t v2to8[]={0, 109, 182, 255};
  static uint8_t pal1[]={
    0, 0, 0, 255,
    255, 255, 255, 255,
  };
  static uint8_t pal2[]={
    0, 0, 0, 255,
    255, 0, 0, 255,
    0, 255, 255, 255,
    255, 255, 255, 255,
  };
  static uint8_t pal4[]={
    0, 0, 0, 255,
    109, 0, 0, 255,
    0, 109, 0, 255,
    109, 109, 0, 255,
    0, 0, 109, 255,
    109, 0, 109, 255,
    0, 109, 109, 255,
    182, 182, 182, 255,
    73, 73, 73, 255,
    255, 0, 0, 255,
    0, 255, 0, 255,
    255, 255, 0, 255,
    0, 0, 255, 255,
    255, 0, 255, 255,
    0, 255, 255, 255,
    255, 255, 255, 255,
  };

  if (verbose) fprintf(stderr, "palette(%d)\n", n);
  switch (n) {
    case 1:
      rv.dat=(rgba_t *)calloc(2, sizeof(rgba_t));
      memcpy(rv.dat, pal1, 6);
      rv.l=2;
      return rv;
    case 2:
      rv.dat=(rgba_t *)calloc(4, sizeof(rgba_t));
      memcpy(rv.dat, pal2, 12);
      rv.l=4;
      return rv;
    case 4:
      rv.dat=(rgba_t *)calloc(16, sizeof(rgba_t));
      memcpy(rv.dat, pal4, 48);
      rv.l=16;
      return rv;
    case 8:
      rv.dat=(rgba_t *)calloc(256, sizeof(rgba_t));
      for(i=0; i<256; i++) {
	rv.dat[i].p[R]=v3to8[(i>>5)&7];
	rv.dat[i].p[G]=v3to8[(i>>2)&7];
	rv.dat[i].p[B]=v2to8[i&3];
	rv.dat[i].p[A]=0xff;
      }
      rv.l=256;
      return rv;
  }
  rv.dat=NULL;
  rv.l=0;
  return rv;
}

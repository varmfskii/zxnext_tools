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
  static uint32_t pal4[]=ULACOLOURS;

  if (get_verbose()>1) fprintf(stderr, "palette(%d)\n", n);
  switch (n) {
    case 1:
      rv=new_pal(2);
      memcpy(rv.dat, pal1, 2*sizeof(rgba_t));
      return rv;
    case 2:
      rv=new_pal(4);
      memcpy(rv.dat, pal2, 4*sizeof(rgba_t));
      return rv;
    case 4:
      rv=new_pal(16);
      memcpy(rv.dat, pal4, 16*sizeof(rgba_t));
      return rv;
    case 8:
      rv=new_pal(256);
      for(i=0; i<256; i++) {
	rv.dat[i].p[R]=v3to8[(i>>5)&7];
	rv.dat[i].p[G]=v3to8[(i>>2)&7];
	rv.dat[i].p[B]=v2to8[i&3];
	rv.dat[i].p[A]=0xff;
      }
      return rv;
  }
  rv.dat=NULL;
  rv.l=0;
  if (get_verbose()>1) fprintf(stderr, "return pal_t: %d\n", rv.l);
  return rv;
}

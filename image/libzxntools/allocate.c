#include <stdlib.h>
#include "zxntools.h"

ixed_t new_ixed(int x, int y, int d) {
  ixed_t rv;
  int i;
  
  if (get_verbose()>1) fprintf(stderr, "new_ixed(%d, %d, %d)\n", x, y, d);
  rv.x=x;
  rv.y=y;
  rv.dat=(uint8_t **)malloc(y*sizeof(uint8_t *)+x*y*sizeof(uint8_t));
  rv.dat[0]=(uint8_t *)(rv.dat+y);
  for(i=1; i<y; i++) rv.dat[i]=rv.dat[0]+rv.x*i;
  rv.pal=new_pal(d);
  return rv;
}

pal_t new_pal(int d) {
  pal_t rv;
  
  if (get_verbose()>1) fprintf(stderr, "new_pal(%d)\n", d);
  rv.l=d;
  rv.dat=(rgba_t *)malloc(d*sizeof(rgba_t));
  return rv;
}

rgb_t new_rgb(int x, int y, int gray) {
  rgb_t rv;
  int i;
  
  if (get_verbose()>1) fprintf(stderr, "new_rgb(%d, %d, %d)\n", x, y, gray);
  rv.x=x;
  rv.y=y;
  rv.gray=gray;
  if (gray) {
    rv.gdat=(uint8_t **)malloc(y*sizeof(uint8_t *)+x*y*sizeof(uint8_t));
    rv.gdat[0]=(uint8_t *)(rv.gdat+y);
    for(i=1; i<y; i++) rv.gdat[i]=rv.gdat[0]+rv.x*i;
  } else {
    rv.dat=(rgba_t **)malloc(y*sizeof(rgba_t *)+x*y*sizeof(rgba_t));
    rv.dat[0]=(rgba_t *)(rv.dat+y);
    for(i=1; i<y; i++) rv.dat[i]=rv.dat[0]+rv.x*i;
  }
  return rv;
}

bm_t new_bm(int x, int y) {
  bm_t rv;
  int i;
  
  if (get_verbose()>1) fprintf(stderr, "new_bm(%d, %d)\n", x, y);
  rv.x=x;
  rv.y=y;
  rv.dat=(uint8_t **)malloc(y*(sizeof(uint8_t *)+(7+x*sizeof(uint8_t))/8));
  rv.dat[0]=(uint8_t *)(rv.dat+y);
  for(i=1; i<y; i++) rv.dat[i]=rv.dat[0]+(7+rv.x)/8*i;
  return rv;
}

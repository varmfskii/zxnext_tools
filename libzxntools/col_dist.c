#include "zxntools.h"

int col_dist(rgba_t a, rgba_t b) {
  int f, d;

  f=(int)a.p[0]-(int)b.p[0];
  d=f*f;
  f=(int)a.p[1]-(int)b.p[1];
  d+=f*f;
  f=(int)a.p[2]-(int)b.p[2];
  d+=f*f;
  return d;
}

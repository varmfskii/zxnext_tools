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

int col_distg(uint8_t a, rgba_t b) {
  int f, d;

  f=(int)a-(int)b.p[0];
  d=900*f*f;
  f=(int)a-(int)b.p[1];
  d+=3481*f*f;
  f=(int)a-(int)b.p[2];
  d+=121*f*f;
  return d;
}

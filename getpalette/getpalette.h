#ifndef GETPALETTE_H
#define GETPALETTE_H
#include "../support/support.h"
#include <stdio.h>

typedef struct pal_t {
  unsigned char *dat;
  int l;
} pal_t;

void writepal(pal_t pal, FILE *out);
pal_t rgb2pal(rgb_t rgb, int len);
#endif

#ifndef IMG2ASM_H
#define IMG2ASM_H
#include <stdio.h>
#include "../support/support.h"

typedef struct pal_t {
  unsigned char *dat;
  int l;
} pal_t;

typedef struct ixed_t {
  unsigned char *dat;
  pal_t pal;
  int x, y;
} ixed_t;

int writeasm(FILE *out, ixed_t ixed, int txsz, int tysz, char *label);
int writepgm(FILE *out, ixed_t ixed, int txsz, int tysz);
int writeraw(FILE *out, ixed_t ixed, int txsz, int tysz);
ixed_t rgb2index(rgb_t rgb, pal_t pal,
  int xoff, int yoff, int xstep, int ystep);
pal_t palette(int n);
pal_t readpal(int len, FILE *palfile);
void showpal(pal_t);
#endif

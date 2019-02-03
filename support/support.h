#ifndef SUPPORT_H
#define SUPPORT_H
#include <stdio.h>

typedef struct rgb_t {
  unsigned char *dat;
  int x,y;
} rgb_t;

rgb_t readppm(FILE *in);
rgb_t readpng(FILE *in);
rgb_t readgif(FILE *in);
rgb_t readbmp(FILE *in);
rgb_t readjpeg(FILE *in);
#endif

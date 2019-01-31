#include <stdio.h>
typedef struct rgb_t {
  unsigned char *dat;
  int x,y;
} rgb_t;

typedef struct pal_t {
  unsigned char *dat;
  int l;
} pal_t;

void writepal(pal_t pal, FILE *out);
rgb_t readppm(FILE *in);
pal_t rgb2pal(rgb_t rgb, int len);

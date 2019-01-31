#include <stdio.h>

typedef struct rgb_t {
  char *dat;
  int x,y;
} rgb_t;

typedef struct pal_t {
  char *dat;
  int l;
} pal_t;

typedef struct ixed_t {
  char *dat;
  pal_t pal;
  int x, y;
} ixed_t;

ixed_t rgb2index(rgb_t rgb, pal_t pal,
  int xoff, int yoff, int xstep, int ystep);
int writeasm(FILE *out, ixed_t ixed, int txsz, int tysz, char *label);
int writepgm(FILE *out, ixed_t ixed, int txsz, int tysz);
int writeraw(FILE *out, ixed_t ixed, int txsz, int tysz);
pal_t palette(int n);
pal_t readpal(int len, FILE *palfile);
rgb_t readimage(FILE *in);

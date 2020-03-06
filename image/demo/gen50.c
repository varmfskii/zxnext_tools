#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct color {
  uint8_t r, g, b;
  float i;
} color;

// gamma corrected
//#define R 0.299
//#define G 0.587
//#define B 0.114
// linear
#define R 0.2126
#define G 0.7152
#define B 0.0722
#define MAX 7
#define NUMCOLS (MAX*7+1)

int cmp(const void *, const void *);
void printcol(color, FILE *, FILE *);

int main() {
  color colors[NUMCOLS];
  int i, j;
  FILE *ppm, *pal;

  for(i=0; i<7; i++) {
    colors[i].r=(i&4)>>2;
    colors[i].g=(i&2)>>1;
    colors[i].b=(i&1)>>0;
    colors[i].i=(colors[i].r*R+colors[i].g*G+colors[i].b*B)*255.0/MAX;
  }
  for(; i<NUMCOLS; i++) {
    colors[i].r=colors[i-7].r+1;
    colors[i].g=colors[i-7].g+1;
    colors[i].b=colors[i-7].b+1;
    colors[i].i=(colors[i].r*R+colors[i].g*G+colors[i].b*B)*255.0/MAX;
  }
  qsort(colors, NUMCOLS, sizeof(color), cmp);
  ppm=fopen("gray50.ppm", "w");
  pal=fopen("gray50c_8.pal", "wb");
  fputs("P3\n16 16\n255\n", ppm);
  for(i=j=0; i<256; i++) {
    if (fabs(i-colors[j].i)>fabs(i-colors[j+1].i))
      if (++j==NUMCOLS-1) break;
    printcol(colors[j], ppm, pal);
    if (i%16==15) putc('\n', ppm);
  }
  for(; i<256; i++) {
    printcol(colors[j], ppm, pal);
    if (i%16==15) putc('\n', ppm);
  }
  fclose(ppm);
  fclose(pal);
}
    
int cmp(const void *a, const void *b) {
  float v = ((color *)a)->i-((color *)b)->i;
  return (v<0)?-1:((v>0)?1:0);
}

void printcol(color c, FILE *ppm, FILE *pal) {
  int i=c.i+0.5;
  //fprintf(ppm, "%d %d %d ", c.r, c.g, c.b);
  fprintf(ppm, "%d %d %d ", i, i, i);
  printf("%d ", i);
  putc(c.r*255/7, pal);
  putc(c.g*255/7, pal);
  putc(c.b*255/7, pal);
  putc('\377', pal);
}


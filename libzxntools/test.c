#include <stdio.h>
#include <stdlib.h>
#include "zxntools.h"

#define TESTIN "testin.ppm"
#define RGB "rgb.ppm"
#define DEC "dec.ppm"
#define IXGY "ixed.pgm"
#define IXCOL "ixed.ppm"
#define PAL "pal.raw"

int verbose=2;

int main() {
  FILE *in, *out;
  rgb_t rgb, dec;
  ixed_t ixed;
  pal_t pal;
  int xoff, yoff, xskip, yskip;
  
  if (!(in=fopen(TESTIN, "r"))) {
    fprintf(stderr, "Unable to open %s\n", TESTIN);
    return 1;
  }
  fprintf(stderr, "start:\n");
  rgb=readrgb(in);
  fprintf(stderr, "readrgb:\n");
  fclose(in);
  if (!(out=fopen(RGB, "w"))) {
    fprintf(stderr, "Unable to open %s\n", RGB);
    return 1;
  }
  writergb(rgb, out);
  fprintf(stderr, "writergb:\n");
  fclose(out);
  xskip=rgb.x/256;
  yskip=rgb.y/192;
  xoff=(rgb.x-xskip*256)/2;
  yoff=(rgb.y-yskip*192)/2;
  dec=decimate(rgb, xoff, yoff, xskip, yskip);
  fprintf(stderr, "decimate:\n");
  free_rgb(rgb);
  if (!(out=fopen(DEC, "w"))) {
    fprintf(stderr, "Unable to open %s\n", DEC);
    return 1;
  }
  writergb(dec, out);
  fprintf(stderr, "writergb-dec\n");
  free_rgb(dec);
  if (!(in=fopen(TESTIN, "r"))) {
    fprintf(stderr, "Unable to open %s\n", TESTIN);
    return 1;
  }
  pal=palette(8);
  ixed=readixed(in, pal);
  fprintf(stderr, "readixed:\n");
  if (!(out=fopen(IXGY, "w"))) {
    fprintf(stderr, "Unable to open %s\n", IXGY);
    return 1;
  }
  writeixed(ixed, 1, out);
  fprintf(stderr, "writeixed-gray:\n");
  fclose(out);
  if (!(out=fopen(IXCOL, "w"))) {
    fprintf(stderr, "Unable to open %s\n", IXGY);
    return 1;
  }
  writeixed(ixed, 0, out);
  fprintf(stderr, "writeixed-color:\n");
  fclose(out);
  free_ixed(ixed);
  if (!(out=fopen(PAL, "w"))) {
    fprintf(stderr, "Unable to open %s\n", PAL);
    return 1;
  }
  writepal(pal, out);
  fprintf(stderr, "writepal:\n");
  fclose(out);
  free_pal(pal);
  if (!(in=fopen(PAL, "r"))) {
    fprintf(stderr, "Unable to open %s\n", PAL);
    return 1;
  }
  pal=readpal(256, in);
  fprintf(stderr, "readpal:\n");
  showpal(pal, stderr);
  fprintf(stderr, "showpal:\n");
  free_pal(pal);
  return 0;
}

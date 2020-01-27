#include "zxntools.h"
#include <stdlib.h>

int verbose=0;
  
int get_verbose(void) {
  return verbose;
}

int libzxntoolsver(int print) {
  if (print)
    fprintf(stderr, "ZX Next Tools version %d.%02d.%02d %s\n",
	    ZXNV>>16, (ZXNV>>8)&0xff, ZXNV&0xff, ZXND);
  return ZXNV;
}

void nextpal(pal_t pal, FILE *out) {
  int i, c, v;

  if (get_verbose()>1)
    fprintf(stderr, "nextpal(pal_t: %d, %p)\n", pal.l, (void *)out);
  for(i=0; i<256 && i<pal.l; i++) {
    for(v=c=0; c<3; c++)
      v=(v<<3)|PAL8TO3(pal.dat[i].p[c]);
    putc(v>>1, out);
    putc(v&0x001, out);
  }
}

ixed_t readixed(struct pam *in, pal_t pal) {
  ixed_t out;
  rgb_t rgb;

  if (get_verbose()>1)
    fprintf(stderr, "readixed(%p, pal_t: %d)\n", (void *) in, pal.l);
  rgb=readrgb(in);
  out=rgb2index(rgb, pal);
  free_rgb(rgb);
  if (get_verbose()>1) fprintf(stderr, "return ixed_t: %dx%d\n", out.x, out.y);
  return out;
}

void set_verbose(int v) {
  verbose=v;
}

void showpal(pal_t pal, FILE *out) {
  int i, j;
  
 if (get_verbose()>1)
    fprintf(stderr, "showpal(%d, %p)\n", pal.l, (void *) out);
  for(i=0; i<pal.l; i++) {
    fprintf(out, "%d: ", i);
    for(j=0; j<3; j++) fprintf(out, "%d ", pal.dat[i].p[j]);
    fprintf(out, "%d\n", pal.dat[i].p[3]);
  }
}

void writebm(bm_t bm, FILE *out) {
  if (get_verbose()>1) fprintf(stderr, "writebm(bm_t: %dx%d, %p)\n",
		       bm.x, bm.y, (void *) out);
  fprintf(out, "P4\n%d %d\n", bm.x, bm.y);
  fwrite(bm.dat[0], 1, (bm.x+7)/8*bm.y, out);
}

void writepal(pal_t pal, FILE *out) {
  if (get_verbose()>1)
    fprintf(stderr, "writepal(%d, %p)\n", pal.l, (void *) out);
  fwrite(pal.dat, pal.l, sizeof(rgba_t), out);
}

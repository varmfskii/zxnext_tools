#include "zxntools.h"
#include <stdlib.h>

/*
 * readpal(): read a palette from a raw binary file
 */

pal_t readpal(int len, FILE *in) {
  pal_t pal;
  int readlen;

  if (verbose) fprintf(stderr, "readpal(%d, %08llx)\n", len, (long long) in);
  pal.dat=(rgba_t *)calloc(len, sizeof(rgba_t));
  readlen=fread(pal.dat, len, sizeof(rgba_t), in);
  if (readlen!=len*sizeof(rgba_t)) {
    fprintf(stderr, "palette file does not match length\n");
    free_pal(pal);
  } else
    pal.l=len;
  return pal;
}

#include "zxntools.h"
#include <stdlib.h>

/*
 * readpal(): read a palette from a raw binary file
 */

pal_t readpal(int len, FILE *in) {
  pal_t pal;
  int readlen;

  if (get_verbose()>1) fprintf(stderr, "readpal(%d, %p)\n", len, (void *) in);
  pal.dat=(rgba_t *)calloc(len, sizeof(rgba_t));
  readlen=fread(pal.dat, sizeof(rgba_t), len, in);
  if (readlen!=len) {
    fprintf(stderr, "palette file does not match length\n");
    free_pal(pal);
  } else
    pal.l=len;
  if (get_verbose()>1) fprintf(stderr, "return pal_t: %d\n", pal.l);
  return pal;
}

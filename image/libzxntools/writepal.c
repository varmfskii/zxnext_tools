#include <stdio.h>
#include "zxntools.h"

void writepal(pal_t pal, FILE *out) {
  if (verbose>1)
    fprintf(stderr, "writepal(%d, %p)\n", pal.l, (void *) out);
  fwrite(pal.dat, pal.l, sizeof(rgba_t), out);
}

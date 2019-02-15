#include <stdio.h>
#include "zxntools.h"

void writepal(pal_t pal, FILE *out) {
  if (verbose)
    fprintf(stderr, "writepal(%d, %08llx)\n", pal.l, (long long) out);
  fwrite(pal.dat, pal.l, sizeof(rgba_t), out);
}

#include <stdio.h>
#include "zxntools.h"

void writebm(bm_t bm, FILE *out) {
  if (verbose>1) fprintf(stderr, "writebm(bm_t: %dx%d, %p)\n",
		       bm.x, bm.y, (void *) out);
  fprintf(out, "P4\n%d %d\n", bm.x, bm.y);
  fwrite(bm.dat[0], 1, (bm.x+7)/8*bm.y, out);
}

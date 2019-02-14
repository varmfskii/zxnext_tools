#include <stdio.h>
#include "support.h"

void showpal(pal_t pal, FILE *out) {
  int i, j;
  
 if (verbose)
    fprintf(stderr, "showpal(%d, %08llx)\n", pal.l, (long long) out);
  for(i=0; i<pal.l; i++) {
    fprintf(out, "%d: ", i);
    for(j=0; j<3; j++) fprintf(out, "%d ", pal.dat[i].p[j]);
    fprintf(out, "%d\n", pal.dat[i].p[3]);
  }
}

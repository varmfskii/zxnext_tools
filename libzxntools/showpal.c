#include <stdio.h>
#include "zxntools.h"

void showpal(pal_t pal, FILE *out) {
  int i, j;
  
 if (verbose>1)
    fprintf(stderr, "showpal(%d, %p)\n", pal.l, (void *) out);
  for(i=0; i<pal.l; i++) {
    fprintf(out, "%d: ", i);
    for(j=0; j<3; j++) fprintf(out, "%d ", pal.dat[i].p[j]);
    fprintf(out, "%d\n", pal.dat[i].p[3]);
  }
}

#include <stdio.h>
#include "support.h"

void writeixed(ixed_t v, int gray, FILE *out) {
  int i, max;

  if (verbose)
    fprintf(stderr, "writeixed(v, %d, %08llx)\n", gray, (long long) out);
  if (gray) {
    max=0;
    for(i=0; i<v.x*v.y; i++)
      if (v.dat[0][i]>max) max=v.dat[0][i];
    fprintf(out, "P5\n%d %d\n%d\n", v.x, v.y, max);
    fwrite(v.dat[0], v.x, v.y, out);
  } else {
    fprintf(out, "P6\n%d %d\n255\n", v.x, v.y);
    for(i=0; i<v.x*v.y; i++)
      fwrite(v.pal.dat[v.dat[0][i]].p, 3, 1, out); 
  }
}

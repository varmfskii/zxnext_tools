#include "getpalette.h"
#include <stdio.h>

void writeraw(pal_t pal, FILE *out) {
  int i;

  for(i=0; i<3*pal.l; i++) putc(pal.dat[i], out);
}

void writeasm(pal_t pal, FILE *out, char *label) {
  int i, v;
  
  fprintf(out, "%s:\n", label);
  for(i=0; i<pal.l; i++) {
    v=(pal.dat[i*3]*14+1)/510;
    v=(v<<3)+(pal.dat[i*3+1]*14+1)/510;
    v=(v<<3)+(pal.dat[i*3+2]*14+1)/510;
    if ((i%8)==0) {
      fprintf(out, "\tdefb $%02x,%02x", v>>1, v&1);
    } else if ((i%8)==7) {
      fprintf(out, ",$%02x,$%02x\n", v>>1, v&1);
    } else {
      fprintf(out, ",$%02x,$%02x", v>>1, v&1);
    }
  }
  if ((i%8)!=0) putc('\n', out);
  fprintf(out, "%s_end:\n", label);
}

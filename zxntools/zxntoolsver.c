#include <stdio.h>
#include "zxntools.h"

int zxntoolsver(int print) {
  if (print)
    fprintf(stderr, "ZX Next Tools version %d.%02d.%02d %s\n",
	    ZXNV>>16, (ZXNV>>8)&0xff, ZXNV&0xff, ZXND);
  return ZXNV;
}
  

#include <stdio.h>
#include <stdlib.h>
#include "zxnftp.h"

void cmd_get(char **params) {
  int i, len;
  char *data, *src, *dest;
  char buf[BLKSZ];
  FILE *out;
  
  if (i<2 || i>3) {
    printerr("Incorrect number of arguments. get <file> [<file>]\n");
    return;
  }
  src=(i==2)?params[1]:params[2];
  dest=params[1];
  data=call_get(src, &len);
  if (!data) {
    printerr("no data\n");
    return;
  }
  if (!(out=fopen(dest, "w"))) {
    sprintf(buf, "Unable to open %s\n", dest);
    printerr(dest);
    return;
  }
  fwrite(data, len, 1, out);
  fclose(out);
  printout("Ok\n");
  return;
}

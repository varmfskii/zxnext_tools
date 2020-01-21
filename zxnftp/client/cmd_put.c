#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "zxnftp.h"

void cmd_put(char **params) {
  int pc;
  char *src, *dest;
  FILE *in;
  struct stat st;
  char buf[BLKSZ];
  
  for(pc=0; params[pc]; pc++);
  if (pc<2 || pc>3) {
    printerr("Incorrect number of arguments. put <file> [<file>]\n");
    return;
  }
  src=(pc==2)?params[1]:params[2];
  dest=params[1];
  stat(src, &st);
  if (st.st_size>fdata_sz) {
    fdata_sz=st.st_size;
    free(fdata);
    fdata=(char *)malloc(fdata_sz);
  }
  if (!(in=fopen(src, "r"))) {
    sprintf(buf, "unable to open local file: %s\n", src);
    printerr(buf);
  }
  fread(fdata, 1, st.st_size, in);
  fclose(in);
  call_put(dest, st.st_size);
}

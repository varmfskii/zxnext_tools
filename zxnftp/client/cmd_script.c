#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "zxnftp.h"

void cmd_script(char **params) {
  int pc;
  char *line;
  char buf[BLKSZ];
  FILE *in;
  
  for(pc=0; params[pc]; pc++);
  if (pc!=2) {
    printerr("Incorrect number of arguments. script <file>\n");
    return;
  }
  if (!(in=fopen(params[1], "r"))) {
    sprintf(buf, "unable to open local file: %s\n", params[1]);
    printerr(buf);
  }
  while((line=readline(in))) {
    execute(line);
    free(line);
  }
  fclose(in);
}

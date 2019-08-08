#include <stdlib.h>
#include <sys/stat.h>
#include "zxnftp.h"

void cmd_put(char **params) {
  int i;
  char *src, *dest;
  FILE *in;
  struct stat st;
  
  wmove(status, 0, 0);
  wdeleteln(status);
  waddstr(status, "put(");
  for(i=1; params[i]; i++) {
    waddch(status, '(');
    waddstr(status, params[i]);
    waddch(status, ')');
  }
  waddch(status, ')');
  if (i<2 || i>3) {
    waddstr(win, "Error: Incorrect number of arguments. put <file> [<file>]\n");
    return;
  }
  src=(i==2)?params[1]:params[2];
  dest=params[1];
  stat(src, &st);
  if (st.st_size>fdata_sz) {
    fdata_sz=st.st_size;
    free(fdata);
    fdata=(char *)malloc(fdata_sz);
  }
  if (!(in=fopen(src, "r"))) {
    waddstr(win, "Error: unable to open local file: ");
    waddstr(win, src);
    waddch(win, '\n');
    return;
  }
  fread(fdata, 1, st.st_size, in);
  fclose(in);
  call_put(dest, st.st_size);
}

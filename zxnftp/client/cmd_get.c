#include <stdlib.h>
#include "zxnftp.h"

void cmd_get(char **params) {
  int i, len, numpar;
  char *data, *src, *dest;
  FILE *out;
  
  wmove(status, 0, 0);
  wdeleteln(status);
  waddstr(status, "get(");
  for(i=1; params[i]; i++) {
    waddch(status, '(');
    waddstr(status, params[i]);
    waddch(status, ')');
  }
  waddch(status, ')');
  if (i<2 || i>3) {
    waddstr(win, "Error: Incorrect number of arguments. get <file> [<file>]\n");
    return;
  }
  src=(i==2)?params[1]:params[2];
  dest=params[1];
  data=call_get(src, &len);
  if (!data) {
    waddstr(win, "Error: no data\n");
    return;
  }
  if (!(out=fopen(dest, "w"))) {
    waddstr(win, "Error: unable to open ");
    waddstr(win, dest);
    waddch(win, '\n');
    return;
  }
  fwrite(data, len, 1, out);
  waddstr(win, "Ok\n");
  return;
}

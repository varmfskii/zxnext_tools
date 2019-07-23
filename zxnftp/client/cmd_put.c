#include <stdlib.h>
#include "zxnftp.h"

void cmd_put(char **params) {
  int i, numpar, rlen;
  char *src, *dest, buf[BLKSZ];
  FILE *in;
  size_t len;
  
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
  if (!(in=fopen(src, "r"))) {
    waddstr(win, "Error: unable to open local file: ");
    waddstr(win, src);
    waddch(win, '\n');
    return;
  }
  for(rlen=len=0; ;) {
#ifdef DEBUG
    sprintf(buf, "%d %d %d\n", data_sz-len, len, data_sz);
    waddstr(debug, buf);
    wrefresh(debug);
#endif
    rlen=fread(data+len, 1, data_sz-len, in);
    len+=rlen;
    if (len!=data_sz) break;
    data_sz*=2;
    data=(char *)realloc(data, data_sz);
  }
#ifdef DEBUG
    sprintf(buf, "%d %d %d\n", rlen, len, data_sz);
    waddstr(debug, buf);
    wrefresh(debug);
#endif
  fclose(in);
#ifdef DEBUG
  sprintf(buf, "%d bytes\n", len);
  waddstr(debug, buf);
  wrefresh(debug);
#endif
  call_put(dest, len);
}

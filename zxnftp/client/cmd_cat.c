#include <stdlib.h>
#include "zxnftp.h"

void cmd_cat(char **params) {
  int i, len;
  char *filedata;
  
  wmove(status, 0, 0);
  wdeleteln(status);
  waddstr(status, "cat(");
  for(i=1; params[i]; i++) {
    waddch(status, '(');
    waddstr(status, params[i]);
    waddch(status, ')');
  }
  waddch(status, ')');
  if (!params[1] || params[2]) {
    waddstr(win, "Error: Incorrect number of arguments. cat <file>\n");
    return;
  }
  filedata=call_get(params[1], &len);
  if (!filedata) return;
  for(i=0; i<len; i++) waddch(win, filedata[i]);
  waddstr(win, "\nOk\n");
}

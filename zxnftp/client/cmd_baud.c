#include <curses.h>
#include "zxnftp.h"

void cmd_baud(char **params) {
  int i;
  
  wmove(status, 0, 0);
  wdeleteln(status);
  waddstr(status, "baud(");
  for(i=1; params[i]; i++) {
    waddch(status, '(');
    waddstr(status, params[i]);
    waddch(status, ')');
  }
  waddch(status, ')');
  if (!params[1] || params[2]) {
    waddstr(win, "Error: Incorrect number of arguments. rm <file/dir>\n");
    return;
  }
  call_simple("BD", params[1]);
  return;
}

#include <curses.h>
#include "zxnftp.h"

void cmd_rmdir(char **params) {
  int i;
  
  wmove(status, 0, 0);
  wdeleteln(status);
  waddstr(status, "rmdir(");
  for(i=1; params[i]; i++) {
    waddch(status, '(');
    waddstr(status, params[i]);
    waddch(status, ')');
  }
  waddch(status, ')');
  if (!params[1] || params[2]) {
    waddstr(win, "Error: Incorrect number of arguments. rmdir <dir>\n");
    return;
  }
  call_simple("RD", params[1]);
  return;
}

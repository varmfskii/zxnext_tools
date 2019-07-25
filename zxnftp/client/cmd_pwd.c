#include <curses.h>
#include "zxnftp.h"

void cmd_pwd(char **params) {
  int i;
  char buf[BLKSZ];
  
  wmove(status, 0, 0);
  wdeleteln(status);
  waddstr(status, "pwd(");
  for(i=1; params[i]; i++) {
    waddch(status, '(');
    waddstr(status, params[i]);
    waddch(status, ')');
  }
  waddch(status, ')');
  if (params[1]) {
    waddstr(win, "Error: Incorrect number of arguments. pwd\n");
    return;
  }
  nettxln("PD");
  netrxln(buf);
  waddstr(win, buf);
  waddch(win, '\n');
  waddstr(win, "Ok\n");
  return;
}

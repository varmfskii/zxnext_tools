#include <curses.h>
#include <stdlib.h>
#include "zxnftp.h"

void cmd_quit(char **params) {
  int i;
  
  wmove(status, 0, 0);
  wdeleteln(status);
  waddstr(status, "exit(");
  if (params)
    for(i=1; params[i]; i++) {
      waddch(status, '(');
      waddstr(status, params[i]);
      waddch(status, ')');
    }
  waddch(status, ')');
  if (params && params[1]) {
    waddstr(win, "Error: Incorrect number of arguments. exit\n");
    finish();
    exit(1);
  }
  call_simple("QU", NULL);
  finish();
  exit(0);
}

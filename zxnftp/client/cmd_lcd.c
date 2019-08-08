#include <curses.h>
#include <unistd.h>
#include "zxnftp.h"

void cmd_lcd(char **params) {
  int i;
  
  wmove(status, 0, 0);
  wdeleteln(status);
  waddstr(status, "lcd(");
  for(i=1; params[i]; i++) {
    waddch(status, '(');
    waddstr(status, params[i]);
    waddch(status, ')');
  }
  waddch(status, ')');
  if (!params[1] || params[2]) {
    waddstr(win, "Error: Incorrect number of arguments. lcd <dir>\n");
    return;
  }
  if (chdir(params[1]))
    waddstr(win, "Unable to change directory\n");
  return;
}

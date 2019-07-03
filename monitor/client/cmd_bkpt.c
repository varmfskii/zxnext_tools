#include "client.h"
#include <curses.h>

void cmd_bkpt(char **parameters) {
  int i;

  wmove(status, 0, 0);
  wdeleteln(status);
  waddstr(status, "breakpoint");
  for(i=1; parameters[i]; i++) {
    waddch(status, '(');
    waddstr(status, parameters[i]);
    waddch(status, ')');
  }
}


  

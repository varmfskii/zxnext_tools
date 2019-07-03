#include "client.h"
#include <curses.h>

void cmd_edit(char **parameters) {
  int i;

  wmove(status, 0, 0);
  wdeleteln(status);
  waddstr(status, "editor");
  for(i=1; parameters[i]; i++) {
    waddch(status, '(');
    waddstr(status, parameters[i]);
    waddch(status, ')');
  }
}


  

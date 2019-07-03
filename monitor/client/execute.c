#include "client.h"
#include <curses.h>
#include <stdlib.h>
#include <string.h>

void execute(char *command) {
  int i;
  char **fields;
  
  fields=parse(command);
  for(i=0; commands[i].name; i++) {
    if (!strcmp(fields[0], commands[i].name)) break;
  }
  if (commands[i].name) {
    commands[i].routine(fields);
  } else {
    wmove(status, 0, 0);
    wdeleteln(status);
    waddstr(status, "execute(");
    for(i=0; fields[i]; i++) {
      waddch(status, '(');
      waddstr(status, fields[i]);
      waddch(status, ')');
    }
    waddch(status, ')');
  }
}

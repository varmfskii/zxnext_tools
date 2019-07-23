#include "zxnftp.h"
#include <curses.h>
#include <stdlib.h>
#include <string.h>

void execute(char *command) {
  int i;
  char **fields;
  
  waddch(win, '\n');
  if (!*command) return;
  fields=parse(command);
  for(i=0; commands[i].name; i++) {
    if (!strcasecmp(fields[0], commands[i].name)) break;
  }
  if (commands[i].name) 
    commands[i].routine(fields);
  else 
    waddstr(win, "Error: unknown command\n");
}

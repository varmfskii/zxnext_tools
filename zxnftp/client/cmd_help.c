#include <string.h>
#include "zxnftp.h"

void cmd_help(char **params) {
  int i;
  
  if (!params[1]) {
    waddstr(win, "Available commands are:\n");
    for(i=0; commands[i].name; i++) {
      waddch(win, '\t');
      waddstr(win, commands[i].use);
      waddch(win, '\n');
    }
    waddstr(win, "Ok\n");
    return;
  }
  if (params[2]) {
    waddstr(win, "Error: incorrect number of parameters. help [<command>]\n");
    return;
  }
  for(i=0; commands[i].name; i++)
    if (!strcmp(params[1], commands[i].name)) {
      waddstr(win, commands[i].help);
      waddstr(win, "Ok\n");
      return;
    }
  waddstr(win, "Error: unknown command\n");
  return;
}

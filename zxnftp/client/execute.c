#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zxnftp.h"

void execute(char *command) {
  int i, c;
  char **fields;
  FILE *cmd;
  
#ifdef CURSES
  printch('\n');
#endif
  if (!*command || *command=='#') return;
  if (*command=='!') {
    cmd=popen(command+1, "r");
    while((c=getc(cmd))!=EOF) printch(c);
    return;
  }
  fields=parse(command);
  for(i=0; commands[i].name; i++) {
    if (!strcasecmp(fields[0], commands[i].name)) break;
  }
  if (commands[i].name) 
    commands[i].routine(fields);
  else 
    printerr("unknown command\n");
}

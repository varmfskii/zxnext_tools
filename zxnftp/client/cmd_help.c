#include <string.h>
#include "zxnftp.h"

void cmd_help(char **params) {
  int i;
  
  if (!params[1]) {
    printout("Available commands are:\n");
    for(i=0; commands[i].name; i++) {
      printch('\t');
      printout(commands[i].use);
      printch('\n');
    }
    printout("Ok\n");
    return;
  }
  if (params[2]) {
    printerr("incorrect number of parameters. help [<command>]\n");
    return;
  }
  for(i=0; commands[i].name; i++)
    if (!strcmp(params[1], commands[i].name)) {
      printout(commands[i].help);
      printout("Ok\n");
      return;
    }
  printerr("unknown command\n");
  return;
}

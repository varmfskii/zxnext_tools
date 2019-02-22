#include <string.h>
#include <ctype.h>
#include "nexcreator.h"

char *commands[]=COMMANDS;

int getcommand(char *line) {
  int i;

  for(i=0; commands[i]; i++)
    if (!strncasecmp(commands[i], line, strlen(commands[i]))) {
      return i+1;
    }
  return 0;
}

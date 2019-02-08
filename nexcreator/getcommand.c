#include <string.h>
#include <ctype.h>
#include "nexcreator.h"

char *commands[]=COMMANDS;

int getcommand(char *line) {
  int i;
  char prefix[6];

  for(i=0; i<5; i++) prefix[i]=toupper(line[i]);
  prefix[5]='\0';
  for(i=0; commands[i]; i++)
    if (!strncmp(commands[i], prefix, strlen(commands[i]))) return i+1;
  return 0;
}

#include <stdlib.h>
#include <ctype.h>

char **parse(char *line) {
  int i, fields;
  char **rv;
  
  for(i=0; isspace(line[i]); i++);
  for(fields=i=0; line[i]; fields++) {
    for(; line[i] && !isspace(line[i]); i++);
    for(; isspace(line[i]); i++);
  }
  rv=(char **)malloc(sizeof(char *)*(fields+1));
  for(; isspace(*line); line++);
  for(i=0; *line; i++) {
    rv[i]=line;
    for(; *line && !isspace(*line); line++);
    for(; isspace(*line); line++) *line='\0';
  }
  rv[i]=NULL;
  return rv;
}

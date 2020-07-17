#include <stdlib.h>

char *getext(char *name) {
  char *ext=NULL;

  for(; *name; name++)
    if (*name=='.') ext=name;
  if (!ext) ext=name;
  return ext;
}

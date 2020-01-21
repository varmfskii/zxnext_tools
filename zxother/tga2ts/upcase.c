#include <ctype.h>

char *upcase(char *s) {
  int i;

  for(i=0; s[i]; i++) s[i]=toupper(s[i]);
  return s;
}

    

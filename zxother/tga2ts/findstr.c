#include <string.h>

char *findstr(char *str, char *tgt) {
  int len=strlen(tgt);
  for(; *str; str++)
    if (!strncmp(str, tgt, len)) return str;
  return NULL;
}

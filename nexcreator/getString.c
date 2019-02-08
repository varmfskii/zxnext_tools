#include <string.h>
#include "nexcreator.h"

void getString(char *dst, int maxlen) {
  int i = 0;
  skipSpace();
  while (i<(maxlen - 2) && *ptr != ',' && *ptr != 0) {
    dst[i++] = *ptr++;
  }
  dst[i] = 0;
}

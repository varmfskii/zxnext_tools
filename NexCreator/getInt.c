#include "NexCreator.h"

int getInt() {
  int i = 0;
  skipSpace();
  if (*ptr == '$') {
    ptr++;
    return getHex();
  }
  while (*ptr != ',' && *ptr) {
    if (*ptr<'0' || *ptr>'9') return 0;
    i = i * 10 + (*ptr++) - '0';
  }
  return i;
}

#include "NexCreator.h"

int getHex() {
  int i = 0;
  skipSpace();
  while (*ptr != ',' && *ptr) {
    if (*ptr >= '0' && *ptr <= '9')
      i = i * 16 + (*ptr++) - '0';
    else if (*ptr >= 'a' && *ptr <= 'f')
      i = i * 16 + (*ptr++) - ('a' - 10);
    else if (*ptr >= 'A' && *ptr <= 'F')
      i = i * 16 + (*ptr++) - ('A' - 10);
    else return 0;
  }
  return i;
}

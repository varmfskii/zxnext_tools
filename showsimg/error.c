#include <stdio.h>
#include <stdlib.h>
#include "showsimg.h"

void error(uint8_t errno, char *s1, char *s2) {
  restorestate(state);
  puts("Error");
  if (s1) {
    for(; *s1; s1++) putchar(*s1);
    if (s2) {
      putchar(' ');
      for(; *s2; s2++) putchar(*s2);
    }
  }
  putchar('\n');
  exit(errno);
}

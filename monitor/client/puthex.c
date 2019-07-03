#include "client.h"
#include <curses.h>

void puthex(WINDOW *win, int c) {
  int x, y;
  char hex[5];

  wmove(win, 0, 0);
  sprintf(hex, "%04x", c&0xffff);
  waddstr(win, hex);
}

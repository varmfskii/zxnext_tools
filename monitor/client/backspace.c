#include "client.h"
#include <curses.h>

void backspace(WINDOW *win) {
  int x, y;

  /*
  getyx(win, y, x);
  if (x!=0) {
    wmove(win, y, x-1);
    wdelch(win);
  }
  */
  waddch(win, '\b');
  wdelch(win);
}

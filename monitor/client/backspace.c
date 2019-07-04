#include "client.h"
#include <curses.h>

void backspace(WINDOW *win) {
  waddch(win, '\b');
  wdelch(win);
}

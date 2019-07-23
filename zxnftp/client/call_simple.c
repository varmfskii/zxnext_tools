#include "zxnftp.h"
#include <curses.h>
#include <string.h>
#include <unistd.h>

void call_simple(char *cmd, char *param) {
  char buf[BLKSZ];
  int i, len;

#ifdef DEBUG
  waddstr(debug, cmd);
  if (param) {
    waddch(debug, ' ');
    waddstr(debug, param);
  }
  waddch(debug, '\n');
  wrefresh(debug);
#endif
#ifndef NONET
  nettxln(cmd);
  if (neterr(NULL)) return;
#ifdef DEBUG
  waddstr(debug, "no error\n");
  wrefresh(debug);
#endif
  if (param) {
#ifdef DEBUG
  waddstr(debug, "parameter: ");
  waddstr(debug, param);
  waddch(debug, '\n');
  wrefresh(debug);
#endif
    nettxln(param);
    if (neterr(NULL)) return;
  }
#endif
  waddstr(win, "Ok\n");
#ifdef DEBUG
  waddstr(debug, cmd);
  if (param) {
    waddch(debug, ' ');
    waddstr(debug, param);
  }
  waddch(debug, '\n');
  wrefresh(debug);
#endif
}

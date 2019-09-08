#include "zxnftp.h"
#ifdef CURSES
#include <curses.h>
#else
#include <stdio.h>
#endif
#include <string.h>
#include <unistd.h>

void call_simple(char *cmd, char *param) {
  nettxln(cmd);
  if (neterr(NULL)) return;
  if (param) {
    nettxln(param);
    if (neterr(NULL)) return;
  }
#ifdef CURSES
  waddstr(win, "Ok\n");
#else
  puts("Ok");
#endif
}

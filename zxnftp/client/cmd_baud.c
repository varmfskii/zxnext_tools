#ifdef CURSES
#include <curses.h>
#else
#include <stdio.h>
#endif
#include "zxnftp.h"

void cmd_baud(char **params) {
  if (!params[1] || params[2]) {
#ifdef CURSES
    waddstr(win, "Error: Incorrect number of arguments. rm <file/dir>\n");
#else
    fputs("Error: Incorrect number of arguments. rm <file/dir>\n", stderr);
#endif
    return;
  }
  call_simple("BD", params[1]);
  return;
}

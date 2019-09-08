#include <stdio.h>
#include "zxnftp.h"

void printerr(char *msg) {
#ifdef CURSES
  waddstr(win, "Error: ");
  waddstr(win, msg);
#else
  fputs("Error: ", stderr);
  fputs(msg, stderr);
#endif
}

void printout(char *msg) {
#ifdef CURSES
  waddstr(win, msg);
#else
  fputs(msg, stdout);
#endif
}

void printch(char c) {
#ifdef CURSES
  waddch(win, c);
#else
  putchar(c);
#endif
}


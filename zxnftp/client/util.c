#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "zxnftp.h"

int cmpls(const void *x, const void *y) {
  return strcmp(*(const char **)x, *(const char **)y);
}

int cmpdir(const void *x, const void *y) {
  return strcmp(29+*(const char **)x, 29+*(const char **)y);
}

void wpause() {
  waddstr(win, "<any key to continue>\n");
  wrefresh(win);
  getch();
}

void error(char *err, int num) {
  finish();
  fprintf(stderr, "%s\n", err);
  exit(num);
}

void backspace(WINDOW *win) {
  waddch(win, '\b');
  wdelch(win);
}

void finish(void) { 
  close(server); 
  endwin();
} 

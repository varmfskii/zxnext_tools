#include "zxnftp.h"
#include <curses.h>
#include <string.h>
#include <unistd.h>

void call_simple(char *cmd, char *param) {
  nettxln(cmd);
  if (neterr(NULL)) return;
  if (param) {
    nettxln(param);
    if (neterr(NULL)) return;
  }
  waddstr(win, "Ok\n");
}

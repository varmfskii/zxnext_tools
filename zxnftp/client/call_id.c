#include "zxnftp.h"
#include <curses.h>
#include <string.h>

void call_id(void) {
  char buf[BLKSZ];
  
  nettxln("ID");
  netrxln(buf);
  id=strdup(buf);
  waddstr(win, id);
  waddch(win, '\n');
}

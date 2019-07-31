#include "zxnftp.h"
#include <curses.h>
#include <unistd.h>

#define LEN 256

int server, w, h;
int disp_mode=NUMERIC;
int port;
char *id, *addr;
char *data, **lines;
size_t data_sz, lines_sz;

WINDOW *status, *win;

int main() {
  int c, done, pos;
  char buffer[LEN];
  
  init();
  refresh();
  //wrefresh(win);
  waddstr(win, "> ");
  wrefresh(win);
  for(pos=done=0; !done;) {
    c=getch();
    switch (c) {
    case '\003': // break
    case '\004': // eof
      cmd_exit(NULL);
      break;
    case KEY_BACKSPACE:
    case '\177':
    case '\b':
      if (pos) {
	pos--;
	backspace(win);
      }
      break;
    case '\n':
    case '\r':
      buffer[pos]='\0';
      execute(buffer);
      pos=0;
      waddstr(win, "> ");
      break;
    default:
      buffer[pos]=c;
      if (pos<LEN-1) {
	pos++;
      } else {
	backspace(win);
      }
      //puthex(status, c);
      waddch(win, c);
    }
    wrefresh(status);
    wrefresh(win);
  }
}

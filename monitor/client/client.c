#include "client.h"
#include <curses.h>
#include <unistd.h>

#define LEN 256

int server, w, h;
int disp_mode=NUMERIC;
WINDOW *status, *win;
#ifdef DEBUG
WINDOW *debug;
#endif
#ifdef NONET
unsigned char mem[0x200000];
#endif

int main() {
  int c, done, pos;
  char buffer[LEN];
  
  init();
  for(pos=done=0; !done;) {
    c=getch();
    switch (c) {
    case '\003': // break
    case '\004': // eof
      done=1;
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
      waddch(win, '\n');
      break;
    case '8': // examine previous
    case '2': // examine next
    case '6': // examine indirect
    case ';': // force numeric
    case '=': // force byte
    case '/': // examine
    case ',': // single step
    default:
      buffer[pos]=c;
      if (pos<LEN-1) {
	pos++;
      } else {
	backspace(win);
      }
      puthex(status, c);
      waddch(win, c);
    }
    wrefresh(status);
    wrefresh(win);
  }
#ifndef NONET
  write(server, "exit", 4);
#endif
  finish();
}

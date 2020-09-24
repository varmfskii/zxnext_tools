#include "zxnftp.h"
#ifdef CURSES
#include <curses.h>
#else
#include <stdio.h>
#endif
#include <unistd.h>

#define LEN 256

int server, w, h;
int disp_mode=NUMERIC;
int port;
char *id, *addr;
char *fdata, *ddata, **lines;
size_t fdata_sz, ddata_sz, lines_sz;

#ifdef CURSES
WINDOW *status, *win;
#ifdef DEBUG
WINDOW *debug;
#endif
#endif

int main(int argc, char *argv[]) {
  int j;
#ifndef CURSES
  int i;
#endif
  int c, done, pos;
  char buffer[LEN];
  
  init();
  
  if (argc > 1) {
    for (j = 1; j < argc; j++) {
      execute(argv[j]);
    }
    cmd_exit(NULL);
    return 0;
  }
  
#ifdef CURSES
  refresh();
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
#else
  for(;;) {
    fputs("> ", stdout);
    fflush(stdout);
    for(i=0; (c=getchar())!=EOF && c!='\n'; )
      if (i<LEN-1) buffer[i++]=c;
    buffer[i]='\0';
    execute(buffer);
    if (c==EOF) cmd_exit(NULL);
  }
#endif
}

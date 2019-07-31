#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "zxnftp.h"

void cmd_ls(char **params) {
  int16_t len;
  int i, y, ix, nlines;
  char buf[BLKSZ], dir[BLKSZ], *p;

  getmaxyx(win, y, i);
  if (params[1]) {
    p=params[1];
  } else {
    nettxln("PD");
    netrxln(dir);
    p=dir;
  }
  nettxln("LS");
  if (neterr(NULL)) return;
  nettxln(p);
  if (neterr(NULL)) return;
  for(i=0; ; i++) {
    nettxln("RR");
    netrxln(buf);
    if (!strncmp("OK", buf, 2)) break;
    netrxln(buf);
    len=strlen(buf);
    if (ix+len+1>data_sz) {
      data_sz*=2;
      data=(char *)realloc(data, data_sz);
    }
    if (i+1>lines_sz) {
      lines_sz*=2;
      lines=(char **)realloc(lines, lines_sz*(sizeof (char *)));
    }
    lines[i]=data+ix;
    strcpy(data+ix, buf);
    ix+=len+1;
  }
  nlines=i;
  qsort(lines, nlines, sizeof(char *), cmpls);
  for(i=0; i<nlines; i++) {
    waddstr(win, lines[i]);
    waddch(win, '\n');
    if (i%(y-1)==y-2) wpause();
  }
  waddstr(win, "Ok\n");
  return;
}

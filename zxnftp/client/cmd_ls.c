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
  for(ix=i=0; ; i++) {
    nettxln("RR");
    netrxln(buf);
    //waddstr(win, buf);
    //waddch(win, '\n');
    if (!strncmp("OK", buf, 2)) break;
    netrxln(buf);
    //waddstr(win, buf);
    //waddch(win, '\n');
    //netrxln(buf);
    //waddstr(win, buf);
    //waddch(win, '\n');
    len=strlen(buf);
    if (ix+len+1>ddata_sz) {
      ddata_sz*=2;
      ddata=(char *)realloc(ddata, ddata_sz);
    }
    if (i+1>lines_sz) {
      lines_sz*=2;
      lines=(char **)realloc(lines, lines_sz*(sizeof (char *)));
    }
    lines[i]=ddata+ix;
    strcpy(ddata+ix, buf);
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

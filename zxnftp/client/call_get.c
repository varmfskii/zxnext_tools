#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#ifdef CURSES
#include <curses.h>
#else
#include <stdio.h>
#endif
#include "zxnftp.h"

/* get a file from the server */
char *call_get(char *param, int *fsize) {
  char buf[BLKSZ];
  int rsize;
  int16_t len;
  struct timespec s, e;
  double time;
#ifdef CURSES
  int y, x;
#endif
  
  gettime(&s);
  nettxln("GT");
  if (neterr(NULL)) return NULL;
  nettxln(param);
  netrxln(buf);
  if (!isdigit(*buf)) {
    neterr(buf);
    return NULL;
  }
  *fsize=atoi(buf);
  sprintf(buf, "%d bytes\n", *fsize);
  printout(buf);
  if (*fsize>fdata_sz) {
    fdata_sz=*fsize;
    free(fdata);
    fdata=(char *)malloc(fdata_sz);
  }
  for(rsize=0; rsize<*fsize; rsize+=len) {
    sprintf(buf, "%d", rsize);
#ifdef CURSES
    waddstr(win, buf);
    wrefresh(win);
    getyx(win, y, x);
    x=0;
    wmove(win, y, x);
#else
    fputs(buf, stdout);
    putchar('\r');
    fflush(stdout);
#endif
    nettxln("RR");
    netrx(fdata+rsize, &len, BLKSZ);
    if (len<0) {
      printerr("Network read error\n");
      nettxln("xx");
      return NULL;
    }
  }
  nettxln("RR");
  if (neterr(NULL)) {
    return NULL;
  }
  gettime(&e);
  time=e.tv_sec-s.tv_sec+(e.tv_nsec-s.tv_nsec)*1e-9;
  sprintf(buf, "%d b, %0.2f s, %0.2f bps\n", *fsize, time, 8**fsize/time);
  printout(buf);
  return fdata;
}
  

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

void call_put(char *param, size_t len) {
  size_t txlen;
  int16_t blen;
  char buf[BLKSZ];
  struct timespec s, e;
#ifdef CURSES
  int y, x;
#endif
  double time;

  gettime(&s);
  nettxln("PT");
  if (neterr(NULL)) return;
  nettxln(param);
  if (neterr(NULL)) return;
  sprintf(buf, "%u", (unsigned int) len);
  nettxln(buf);
  for(txlen=0; txlen<len; txlen+=BLKSZ) {
    netrxln(buf);
    if (strncmp("RR", buf, 2)) {
      neterr(buf);
      return;
    }
    if (len-txlen>BLKSZ)
      blen=BLKSZ;
    else
      blen=len-txlen;
    nettx(fdata+txlen, blen);
    sprintf(buf, "%u", (unsigned int) txlen+blen);
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
  }
  if (!neterr(NULL)) printout("\nOk\n");
  gettime(&e);
  time=e.tv_sec-s.tv_sec+(e.tv_nsec-s.tv_nsec)*1e-9;
  sprintf(buf, "%u b, %0.2f s, %0.2f bps\n", (unsigned int) len, time, 8*len/time);
  printout(buf);
}

#include "zxnftp.h"
#include <curses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void call_put(char *param, size_t len) {
  size_t txlen;
  int16_t blen;
  char buf[BLKSZ];
  struct timespec s, e;
  double time;

  clock_gettime(CLOCK_REALTIME, &s);
  nettxln("PT");
  if (neterr(NULL)) return;
  nettxln(param);
  if (neterr(NULL)) return;
  sprintf(buf, "%d", (int) len);
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
    nettx(data+txlen, blen);
  }
  if (!neterr(NULL)) waddstr(win, "Ok\n");
  clock_gettime(CLOCK_REALTIME, &e);
  time=e.tv_sec-s.tv_sec+(e.tv_nsec-s.tv_nsec)*1e-9;
  sprintf(buf, "%d b, %0.2f s, %0.2f bps\n", len, time, 8*len/time);
  waddstr(win, buf);
}

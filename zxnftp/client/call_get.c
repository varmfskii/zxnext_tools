#include "zxnftp.h"
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

char *call_get(char *param, int *fsize) {
  char buf[BLKSZ];
  int rsize;
  int16_t len;
  struct timespec s, e;
  double time;
  
  clock_gettime(CLOCK_REALTIME, &s);
  nettxln("GT");
  if (neterr(NULL)) return NULL;
  nettxln(param);
  netrxln(buf);
  if (!isdigit(*buf)) {
    neterr(buf);
    return NULL;
  }
  *fsize=atoi(buf);
  if (*fsize>data_sz) {
    data_sz*=2;
    data=(char *)realloc(data, data_sz);
  }
  for(rsize=0; rsize<*fsize; rsize+=len) {
    nettxln("RR");
    netrx(data+rsize, &len, BLKSZ);
  }
  nettxln("RR");
  if (neterr(NULL)) {
    return NULL;
  }
  clock_gettime(CLOCK_REALTIME, &e);
  time=e.tv_sec-s.tv_sec+(e.tv_nsec-s.tv_nsec)*1e-9;
  sprintf(buf, "%d b, 0.2f s, %0.2f bps\n", *fsize, time, 8**fsize/time);
  waddstr(win, buf);
  return data;
}
  

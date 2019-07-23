#include "zxnftp.h"
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

char *call_get(char *param, int *fsize) {
  char buf[BLKSZ];
  int rsize;
  uint8_t len;

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
  return data;
}
  

#include "zxnftp.h"
#include <curses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void call_put(char *param, size_t len) {
  size_t txlen;
  uint8_t blen;
  char buf[BLKSZ];
  
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
}

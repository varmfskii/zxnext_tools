#include "zxnftp.h"
#include <unistd.h>
#include <string.h>

void netrx(char *rx, uint8_t *rlen, uint8_t mode) {
  uint8_t len;
  
  len=read(server, rx, 255);
  switch (mode) {
  case STRING:
    rx[len]='\0';
    break;
  case LINE:
    if (len>=2 && (rx[len-2]=='\n' || rx[len-2]=='\r'))
      rx[len=len-2]='\0';
    else if (len>=1 && (rx[len-1]=='\n' || rx[len-1]=='\r'))
      rx[len=len-1]='\0';
    else
      rx[len]='\0';
    break;
  default:
    *rlen=len;
  }
#ifdef DEBUG
  waddstr(debug, "read: ");
  for(int i=0; i<len; i++) waddch(debug, rx[i]);
  waddch(debug, '\n');
  wrefresh(debug);
#endif
}

void nettx(const char *buff, uint8_t len) {
  uint8_t len1;
  char t[BLKSZ+3];
  const char *out;
  
  if (len==LINE) {
    strcpy(t, buff);
    strcat(t, "\r\n");
    out=t;
  } else
    out=buff;
  if (len==STRING || len==LINE)
    len1=strlen(buff);
  else
    len1=len;
  write(server, buff, len1);
#ifdef DEBUG
  sprintf(t, "write: %d\n", len1);
  waddstr(debug, t);
  wrefresh(debug);
#endif
}

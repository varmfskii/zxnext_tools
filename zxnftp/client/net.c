#include "zxnftp.h"
#include <unistd.h>
#include <string.h>

void netrx(char *rx, int16_t *rlen, int16_t mode) {
  int16_t len;
  
  len=read(server, rx, BLKSZ);
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
}

void nettx(const char *buff, int16_t len) {
  int16_t len1;
  char t[BLKSZ+3];
  const char *out;
  
  if (len==LINE) {
    strcpy(t, buff);
    strcat(t, "\r\n");
    out=t;
  } else
    out=buff;
  if (len==STRING || len==LINE)
    len1=strlen(out);
  else
    len1=len;
  write(server, out, len1);
}

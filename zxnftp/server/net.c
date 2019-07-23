#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zxnftp.h"

void netrx(char *rx, uint8_t *rlen, uint8_t mode) {
  char cbuf[16], lbuf[17];
  uint8_t i, j, start, len;

  i=0;
  for(;;) {
    while((cbuf[i]=uartchar())!=':') {
      i=(i+1)&0x0f;
    }
    for(start=(i-1)&0x0f;
	cbuf[start]!='+' && cbuf[start]!=':';
	start=(start-1)&0x0f);
    for(i=0, j=(start+1)&0x0f; cbuf[j]!=':'; i++, j=(j+1)&0x0f)
      lbuf[i]=cbuf[j];
    lbuf[i]='\0';
    if (strncmp(lbuf, "IPD,0,", 6)) continue;
    for(i=6, len=0; lbuf[i]>='0' && lbuf[i]<='9'; i++)
      len=len*10+lbuf[i]-'0';
    if (!lbuf[i]) break;
  }
  if (len>BLKSZ) {
    netclose();
    exit(1);
  }
  for(i=0; i<len; i++) rx[i]=uartchar();
  switch (mode) {
  case STRING:
    rx[len]='\0';
    break;
  case LINE:
    if (len>=2 && (rx[len-2]=='\n' || rx[len-2]=='\r'))
      rx[len-2]='\0';
    else if (len>=1 && (rx[len-1]=='\n' || rx[len-1]=='\r'))
      rx[len-1]='\0';
    else
      rx[len]='\0';
    break;
  default:
    *rlen=len;
  }
}

void nettx(const char *buff, uint8_t len) {
  char command[19];
  uint8_t len1, len2;

  switch(len) {
  case STRING:
    len1=len2=strlen(buff);
    break;
  case LINE:
    len1=strlen(buff);
    len2=len1+2;
    break;
  default:
    len1=len2=len;
  }
  sprintf(command, "AT+CIPSEND=0,%d\r\n", len2);
  if (cmdresponse(command)) return;
  uartwrite(buff, len1);
  if (len==LINE) uartwrite("\r\n", 2);
  uartresponse();
}

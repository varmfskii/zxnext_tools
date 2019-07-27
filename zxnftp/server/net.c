#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zxnftp.h"

void netrx(char *rx, int16_t *rlen, int16_t mode) {
  char c;
  int16_t i, len;

  i=0;
  for(c='\0';;) {
    while(c!='+') c=uartchar();
    c=uartchar();
    if (c!='I') continue;
    c=uartchar();
    if (c!='P') continue;
    c=uartchar();
    if (c!='D') continue;
    c=uartchar();
    if (c!=',') continue;
    c=uartchar();
    if (c!='0') continue;
    c=uartchar();
    if (c!=',') continue;
    c=uartchar();
    for(len=0; c>='0' && c<='9';) {
      len=len*10+c-'0';
      c=uartchar();
    }
    if (c==':') break;
  }
  //printf("\nblock %d bytes\n", len);
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

void nettx(const char *buff, int16_t len) {
  char command[19];
  int16_t len1, len2;

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

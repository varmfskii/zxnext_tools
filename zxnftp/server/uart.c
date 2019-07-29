#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zxnftp.h"

char cmdresponse(char *cmd) {
  uartwrite(cmd, strlen(cmd));
  return uartresponse();
}

char uartresponse(void) {
  int16_t i, j;
  const char *responses[]={ "OK\r", "ERROR\r", "SEND OK\r", "SEND FAIL\r", NULL };

  i=0;
  for(; i<BLKSZ;)
    if ((line[i++]=uartreadc())=='\n') {
      line[i-1]='\0';
      for(j=0; responses[j]; j++)
	if (!strcmp(line, responses[j])) return j;
      i=0;
    }
  fprintf(stderr, "Line length exceeded\n");
  exit(1);
  return 0xff;
}

void uartread(char *buf, int16_t n) {
  int16_t i;
  
  for(i=0; i<n; i++) buf[i]=uartreadc();
}

void uartwrite(const char *buf, int16_t n) {
  int16_t i;

  for(i=0; i<n; i++) uartwritec(buf[i]);
}

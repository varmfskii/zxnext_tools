#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zxnftp.h"

#define LINESZ 255

uint8_t cmdresponse(char *cmd) {
  uartwrite(cmd, strlen(cmd));
  return uartresponse();
}

uint8_t uartchar(void) {
  while(!TX&UART_DATA);
  return RX;
}
#include <stdio.h>
#include <stdint.h>
#include "zxnftp.h"

uint8_t uartread(char *buf, uint8_t n) {
  uint8_t i;

  for(i=0; i<n && (TX&UART_DATA); i++) {
    buf[i]=RX;
  }
  return i;
}

uint8_t uartresponse(void) {
  char line[LINESZ];
  uint8_t i, j;
  const char *responses[]={ "OK\r", "ERROR\r", "SEND OK\r", "SEND FAIL\r", NULL };

  i=0;
  for(; i<LINESZ;)
    if ((line[i++]=uartchar())=='\n') {
      line[i-1]='\0';
      for(j=0; responses[j]; j++)
	if (!strcmp(line, responses[j])) return j;
      i=0;
    }
  fprintf(stderr, "Line length exceeded\n");
  exit(1);
  return 0xff;
}

void uartwrite(const char *buf, uint8_t n) {
  uint8_t i;

  for(i=0; i<n; i++) {
    while(TX&UART_BUSY);
    TX=buf[i];
  }
  while(TX&UART_BUSY);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zxnftp.h"

char uartchar(void) {
  while(!TX&UART_DATA);
  return RX;
}

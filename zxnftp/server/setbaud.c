#include <stdio.h>
#include "zxnftp.h"

__sfr __banked __at 0x243b NEXT_SEL;
__sfr __banked __at 0x253b NEXT_RW;

const int32_t clks[]={ 28000000, 28571429, 29464286, 30000000,
		     31000000, 32000000, 33000000, 27000000 };

#define MINSUB 12
#define MAXSUB 131071

uint8_t setbaud(int32_t baud) {
  int32_t clk, sub;
  uint8_t r;
  uint16_t i;

  NEXT_SEL=0x11;
  clk=clks[NEXT_RW];
  printf("%d.%06d MHz\n", clk/1000000, clk%1000000);
  sub=(clk+(baud>>1))/baud;
  if (sub<MINSUB) {
    sub=MINSUB;
    baud=(clk+(sub>>1))/sub;
  }
  if (sub>MAXSUB) {
    sub=MAXSUB;
    baud=(clk+(sub>>1))/sub;
  }
  printf("%ld baud=%ld sub\n", baud, sub);
  sprintf(buf, "AT+UART_CUR=%ld,8,1,0,0\r\n", baud);
  if ((r=cmdresponse(buf))) {
    printf("%d\n", r);
    return r;
  }
  RX=sub&0x7f;
  RX=0x80|(sub>>7);
  UART_CTL=0x10|((sub>>14)&0x07);
  for(i=1; i; i++);
  printf("AT\n");
  if ((r=cmdresponse("AT\r\n"))) printf("%d\n", r);
  return r;
}

  

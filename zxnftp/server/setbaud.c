#include <stdio.h>
#include "zxnftp.h"

__sfr __banked __at 0x243b NEXT_SEL;
__sfr __banked __at 0x253b NEXT_RW;

const int32_t clks[]={ 28000000, 28571429, 29464286, 30000000,
		     31000000, 32000000, 33000000, 27000000 };

uint8_t setbaud(int32_t baud) {
  int32_t clk, sub;
  
  NEXT_SEL=0x11;
  clk=clks[NEXT_RW];
  printf("%d.%06d MHz\n", clk/1000000, clk%1000000);
  sub=(clk+baud>>1)/baud;
  printf("%ld baud=%ld sub\n", baud, sub);
  sprintf(buf, "AY+UART_CUR=%ld,8,1,0,0", baud);
  //if (cmdresponse(buf)) return 1;
  //RX=sub&0x7f;
  //RX=sub>>7;
  //return cmdresponse("AT");
  return 0;
}

  

#include "client.h"
#include "server.h"
#include <curses.h>
#include <string.h>
#include <unistd.h>

void call_exec(int addr) {
  char outbuf[20];

  addr&=0xffff;
#ifdef DEBUG
  sprintf(outbuf, "exec address: %04x\n", addr);
  waddstr(debug, outbuf);
#endif
  outbuf[0]=EXEC;
  outbuf[1]=addr&0xff;
  outbuf[2]=addr>>8;
#ifndef NONET
  output(server, outbuf, 3);
#endif
}
  

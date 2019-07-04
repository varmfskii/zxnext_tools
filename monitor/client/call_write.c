#include "client.h"
#include "server.h"
#include <curses.h>
#include <unistd.h>
#include <string.h>

void call_write(int port, int addr, int len, char *buffer) {
  char outbuf[260];
  int len2;

  addr&=0xffff;
  len&=0xff;
  len2=len?len:0x100;
#ifdef DEBUG
  if (port)  
    sprintf(outbuf, "write port address: %04x length %02x\n", addr, len);
  else
    sprintf(outbuf, "write memory address: %04x length %02x\n", addr, len);
  waddstr(debug, outbuf);
#endif
  outbuf[0]=port?PWRITE:MWRITE;
  outbuf[1]=addr&0xff;
  outbuf[2]=addr>>8;
  outbuf[3]=len;
  memcpy(outbuf+4, buffer, len2);
#ifndef NONET
  write(server, outbuf, len2+4);
#endif
}

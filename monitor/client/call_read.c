#include "client.h"
#include "server.h"
#include <curses.h>
#include <unistd.h>

int call_pread(int port, int addr, int len, char *buffer) {
  int len2;
  char temp[256];
  string rx;
  
  addr&=0xffff;
  len&=0xff;
  len2=len?len:0x100;
#ifdef DEBUG
  if (port)
    sprintf(temp, "read port address: %04x length %02x\n", addr, len);
  else
    sprintf(temp, "read memory address: %04x length %02x\n", addr, len);
  waddstr(debug, temp);
#endif
  temp[0]=port?PREAD:MREAD;
  temp[1]=addr&0xff;
  temp[2]=addr>>8;
  temp[3]=len;
#ifndef NONET
  write(server, temp, 4);
  rx=srvr_recv();
  if (rx.len<len2) {
    if (port)
      waddstr(win, "pread: Short read\n");
    else
      waddstr(win, "mread: Short read\n");
    memcpy(buffer, rx.data, rx.len);
  } else if (rx.len>len2) {
    if (port)
      waddstr(win, "pread: Long read\n");
    else
      waddstr(win, "mread: Long read\n");
    memcpy(buffer, rx.data, len2);
  } else {
    memcpy(buffer, rx.data, len2);
  }
  free(rx.data);
#endif
}

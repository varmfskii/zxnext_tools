#include "client.h"
#include "server.h"
#include <unistd.h>

void call_exit(void) {
  char outbuf[1];
#ifdef DEBUG
  waddstr(debug, "exit");
#endif
  outbuf[0]=EXIT;
#ifndef NONET
  write(server, outbuf, 1);
#endif
}

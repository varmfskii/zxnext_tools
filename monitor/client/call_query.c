#include "client.h"
#include "server.h"
#include <unistd.h>
#include <string.h>

string call_query(void) {
  char outbuf[1];
#ifdef NONET
  string rv;

  rv.data=strdup("Test server, no network");
  rv.len=strlen(rv.data+1);
#endif
  outbuf[0]=QUERY;
#ifdef DEBUG
  waddstr(debug, "query\n");
#endif
#ifndef NONET
  write(server, outbuf, 1);
  return srvr_resp();
#else
  return rv;
#endif
}

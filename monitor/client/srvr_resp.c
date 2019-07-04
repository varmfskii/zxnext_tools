#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEN 256

string srvr_resp(void) {
  char buffer[LEN];
  string response;
  int total, len;

  response.data=(char *)malloc(1);
  for(total=1; (len=read(server, buffer, LEN))==LEN; total+=LEN) {
    response.data=(char *)realloc(response.data, total+LEN);
    memcpy(&(response.data[total-1]), buffer, LEN);
  }
  response.data=(char *)realloc(response.data, total+len);
  memcpy(&(response.data[total-1]), buffer, len);
  response.len=total+len;
  response.data[total+len-1]='\0';
}

#include "zxnftp.h"
#include <string.h>

void call_id(void) {
  char buf[BLKSZ];
  
  nettxln("ID");
  netrxln(buf);
  id=strdup(buf);
}

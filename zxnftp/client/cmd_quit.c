#include <stdlib.h>
#include "zxnftp.h"

void cmd_quit(char **params) {
  if (params && params[1]) {
    printerr("Incorrect number of arguments. Usage exit\n");
    finish();
    exit(1);
  }
  call_simple("QU", NULL);
  finish();
  exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include "zxnftp.h"

void cmd_exit(char **params) {
  int i;
  
  if (params && params[1]) {
    printerr("Incorrect number of arguments. exit\n");
    finish();
    exit(1);
  }
  call_simple("XX", NULL);
  finish();
  exit(0);
}

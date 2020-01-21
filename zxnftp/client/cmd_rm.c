#include "zxnftp.h"

void cmd_rm(char **params) {
  if (!params[1] || params[2]) {
    printerr("Incorrect number of arguments. Usage rm <file/dir>\n");
    return;
  }
  call_simple("RM", params[1]);
  return;
}

#include "zxnftp.h"

void cmd_rmdir(char **params) {
  if (!params[1] || params[2]) {
    printerr("Incorrect number of arguments. Usage rmdir <dir>\n");
    return;
  }
  call_simple("RD", params[1]);
  return;
}

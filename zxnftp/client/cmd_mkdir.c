#include "zxnftp.h"

void cmd_mkdir(char **params) {
  if (!params[1] || params[2]) {
    printerr("ncorrect number of arguments. mkdir <dir>\n");
    return;
  }
  call_simple("MD", params[1]);
  return;
}

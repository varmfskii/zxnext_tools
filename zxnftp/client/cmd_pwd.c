#include "zxnftp.h"

void cmd_pwd(char **params) {
  char buf[BLKSZ];
  
  if (params[1]) {
    printerr("Incorrect number of arguments. Usage pwd\n");
    return;
  }
  nettxln("PD");
  netrxln(buf);
  printout(buf);
  printout("\nOk\n");
  return;
}

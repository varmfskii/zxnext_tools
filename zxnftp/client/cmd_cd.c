#include <stdio.h>
#include <string.h>
#include "zxnftp.h"

void cmd_cd(char **params) {
  int len;
  char buf[BLKSZ];
  
  if (!params[1] || params[2]) {
    printerr("Incorrect number of arguments. cd <dir>\n");
    return;
  }
  if (params[1][0] && params[1][1]==':') {
    nettxln("DR");
    if (neterr(NULL)) return;
    buf[0]=params[1][0];
    buf[1]='\0';
    nettxln(buf);
    if (neterr(NULL)) return;
  }
  nettxln("CD");
  if (neterr(NULL)) return;
  len=strlen(params[1]);
  if (len && params[1][len-1]!='/') {
    sprintf(buf, "%s/", params[1]);
    nettxln(buf);
  } else
    nettxln(params[1]);
  if (neterr(NULL)) return;
  printout("Ok\n");
  return;
}

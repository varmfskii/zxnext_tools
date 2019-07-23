#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "zxnftp.h"

void senderr(void) {
  //error(0, errno, "-");
  switch(errno) {
  case ESX_EEXIST:
    nettxln("EX");
    break;
  case ESX_EISDIR:
    nettxln("ID");
    break;
  case ESX_ENOENT:
    nettxln("NE");
    break;
  case ESX_ENOTDIR:
    nettxln("ND");
    break;
  case ESX_EDIRINUSE:
    nettxln("N0");
    break;
  default:
    nettxln("XX");
  }
}

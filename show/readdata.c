#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "show.h"

void readdata(uint8_t in, uint16_t len) {
  errno=0;
  esx_f_read(in, (char *)0xa000, len);
  if (errno) error(errno, "Image Read", NULL);
}

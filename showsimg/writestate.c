#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "showsimg.h"

void writestate(void) {
  uint8_t out;
  errno=0;
  if (opts.layer==LAYER1)
    out=esx_f_open("showsimg.l1", ESX_MODE_W|ESX_MODE_OPEN_CREAT);
  else
    out=esx_f_open("showsimg.l2", ESX_MODE_W|ESX_MODE_OPEN_CREAT);
  if (out==0xff || errno) error(errno,"failed to write state",NULL);
  savestate();
  esx_f_write(out, state, sizeof(nextstate_t));
  esx_f_close(out);
}

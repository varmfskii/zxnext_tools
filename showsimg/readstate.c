#include <stdio.h>
#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "showsimg.h"

void readstate(void) {
  uint8_t in;
  nextstate_t new_state;

  errno=0;
  if (opts.layer==LAYER1) 
    in=esx_f_open("showsimg.l1", ESX_MODE_R);
  else
    in=esx_f_open("showsimg.l2", ESX_MODE_R);
  if (in==0xff || errno) {
    puts("read state error");
    return;
  }
  esx_f_read(in, &new_state, sizeof(nextstate_t));
  restorestate(&new_state);
  esx_f_close(in);
}

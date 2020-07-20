#include <stdio.h>
#include <errno.h>
#include <arch/zxn/esxdos.h>
#include <input.h>
#include "showsimg.h"

nextstate_t *state;
opt_t opts;

int main(int argc, char *argv[]) {
  uint8_t in;
  nextstate_t nextstate;
  
  state=&nextstate;
  nextstate.valid=0;
  getopts(argc, argv);
  if ((in=esx_f_open(opts.name,ESX_MODE_R))==0xff) {
    error(errno, "Unable to open:", opts.name);
  }
#ifdef DEBUG
  if (opts.info) info();
#endif
  if (opts.sread) readstate();
  savestate();
  if (opts.swrite) writestate();
  setstate();
  if (opts.partord==IEP) {
    setimage(in);
    setpalette(in);
  } else {
    setpalette(in);
    setimage(in);
  }
  if (!opts.autoexit) {
    in_wait_key();
    restorestate(state);
  }
  return 0;
}

#include <errno.h>
#include <arch/zxn/esxdos.h>
#include <input.h>
#include "show.h"

nextstate_t *state;
opt_t opts;

int main(int argc, char *argv[]) {
  uint8_t in;
  char *name;
  struct esx_stat stat;
  nextstate_t nextstate;
  
  name=getopts(argc, argv);
  state=&nextstate;
  nextstate.valid=0;
  if (esx_f_stat(name, &stat)==0xff) {
    error(errno, "Unable to stat:", name);
  }
  if (opts.mode==UNKNOWN) guessmode(stat.size);
  savestate();
  setstate();
  if ((in=esx_f_open(name,ESX_MODE_R))==0xff) {
    error(errno, "Unable to open:", name);
  }
  setimage(in);
  setpalette(in);
  if (!opts.autoexit) {
    in_wait_key();
    restorestate();
  }
  return 0;
}

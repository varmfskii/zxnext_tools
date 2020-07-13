#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "zxnext.h"
#include "showsimg.h"

void readdata(uint8_t in, uint16_t len);

void setimage(uint8_t in) {
  uint8_t i;
  
  switch(opts.mode) {
  case ULA:
    SETNEXTREG(R_MMU5, 10);
    readdata(in, 6912);
    break;
  case LORES:
  case HIRES:
  case HICOL:
    SETNEXTREG(R_MMU5, 10);
    readdata(in, 6144);
    pNextDat = 11;
    readdata(in, 6144);
    break;
  case RAD:
    SETNEXTREG(R_MMU5, 10);
    readdata(in, 6144);
    break;
  case L2_256:
  case NXI:
    pNextReg = R_MMU5;
    for(i=L2PAGE; i<L2PAGE+6; i++) {
      pNextDat = i;
      readdata(in, 8192);
    }
    break;
  case L2_320:
  case L2_640:
    pNextReg = R_MMU5;
    for(i=L2PAGE; i<L2PAGE+10; i++) {
      pNextDat = i;
      readdata(in, 8192);
    }
    break;
  }
}

void readdata(uint8_t in, uint16_t len) {
  errno=0;
  esx_f_read(in, (char *)0xa000, len);
  if (errno) error(errno, "Image Read", NULL);
}

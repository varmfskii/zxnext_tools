#include <stdio.h>
#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "zxnext.h"
#include "show.h"

void setpalette(uint8_t in) {
  uint8_t *palette, data[516];
  uint8_t i, attr;
  uint16_t size;
  int ix;

  errno=0;
  size=esx_f_read(in, data, 516);
  if (errno) error(errno, "Read Palette", NULL);
  if (!size) return;
  if (size%2) {
    palette=&data[1];
    size--;
    if (opts.mode==HIRES) {
      pTimex=data[0];
      attr=0;
    } else {
      attr=data[0];
    }
  } else {
    palette=data;
    attr=0;
  }
  if (!opts.ulaplus && !opts.palbits) {
    if (opts.mode&TIMEX) {
      if (size==64) opts.ulaplus=1;
      else if (!attr && size==16) opts.palbits=8;
      else if (!attr && size==32) opts.palbits=9;
      else if (256/(attr+1)+attr+1==size) opts.palbits=8;
      else if (2*(256/(attr+1)+attr+1)==size) opts.palbits=9;
      else if (size<=256) opts.palbits=8;
      else opts.palbits=9;
    } else {
      if ((opts.mode==L2_640 && size==32)
	  || size>256) opts.palbits=9;
      else opts.palbits=8;
    }
  }
  pNextReg=R_PALCTL;
  if (attr) pNextDat=0x01;
  if (opts.ulaplus) {
    SETNEXTREG(R_ULACTL, 0x08);
    pULAPlusReg = 0x40;
    SETNEXTREG(R_PALIDX, 0xc0);
    pNextReg = R_PALVAL8;
    for(i=0; i<64 && i<size; i++) {
      pULAPlusReg = i;
      pULAPlusDat = palette[i];
    }
  } else if (opts.palbits==8) {
    SETNEXTREG(R_PALIDX, 0);
    pNextReg = R_PALVAL8; 
    if (attr) {
      for(ix=0; ix<=attr; ix++) pNextDat = palette[ix];
      SETNEXTREG(R_PALIDX, 0x80);
      pNextReg = R_PALVAL8; 
      for(; ix<=size; ix++) pNextDat = palette[ix];
    } else {
      for(ix=0; ix<=size; ix++) pNextDat = palette[ix];
    }
  } else {
    SETNEXTREG(R_PALIDX, 0);
    pNextReg = R_PALVAL9; 
    if (attr) {
      for(ix=0; ix<=2*attr; ix++) pNextDat = palette[ix];
      SETNEXTREG(R_PALIDX, 0x80);
      pNextReg = R_PALVAL9; 
      for(; ix<=size; ix++) pNextDat = palette[ix];
    } else {
      for(ix=0; ix<=size; ix++) pNextDat = palette[ix];
    }
  }
}

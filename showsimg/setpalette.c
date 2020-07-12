#include <stdio.h>
#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "zxnext.h"
#include "showsimg.h"

void setpalette(uint8_t in) {
  uint8_t *palette, data[516];
  uint8_t i, attr;
  int ix;

  if (!opts.size && !opts.extra) {
    if (opts.mode==LORES) {
      SETNEXTREG(R_PALCTL, 0x00);
      SETNEXTREG(R_PALIDX, 0);
      pNextReg = R_PALVAL8;
      for(ix=0; ix<256; ix++) pNextDat=ix;
    }
    return;
  }
  errno=0;
  opts.size=esx_f_read(in, data, opts.size+opts.extra);
  if (errno) error(errno, "Read Palette", NULL);
  if (opts.extra) {
    palette=&data[1];
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
  if (attr)
    SETNEXTREG(R_PALCTL, 0x01);
  else if ((opts.mode&LAYER)==L1)
    SETNEXTREG(R_PALCTL, 0x00);
  else
    SETNEXTREG(R_PALCTL, 0x10);
  if ((opts.palette&PTYPE)==ULAPLUS) {
    SETNEXTREG(R_ULACTL, 0x08);
    pULAPlusReg = 0x40;
    SETNEXTREG(R_PALIDX, 0xc0);
    pNextReg = R_PALVAL8;
    for(i=0; i<64 && i<opts.size; i++) {
      pULAPlusReg = i;
      pULAPlusDat = palette[i];
    }
  } else {
    SETNEXTREG(R_PALIDX, 0);
    if ((opts.palette&PDEPTH)==P8)
      pNextReg = R_PALVAL8;
    else
      pNextReg = R_PALVAL9;
    if ((opts.palette&PTYPE)==PNORM) {
      for(ix=0; ix<opts.size; ix++) pNextDat=palette[ix];
    } else if (attr==0xff) {
      for(ix=0; ix<opts.size-1; ix++) pNextDat=palette[ix];
      SETNEXTREG(R_GLBLTRANS, palette[ix]);
    } else {
      if ((opts.palette&PDEPTH)==P8) {
	for(ix=0; ix<=attr && ix<opts.size; ix++) pNextDat=palette[ix];
	SETNEXTREG(R_PALIDX, 0x80);
	pNextReg = R_PALVAL8; 
	for(ix=0; ix<opts.size; ix++) pNextDat=palette[ix];	
      } else {
	for(ix=0; ix<=attr<<1 && ix<opts.size; ix++) pNextDat=palette[ix];
	SETNEXTREG(R_PALIDX, 0x80);
	pNextReg = R_PALVAL9; 
      }
      for(; ix<opts.size; ix++) pNextDat=palette[ix];	
    }
  }
}

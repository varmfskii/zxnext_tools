#include <stdio.h>
#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "zxnext.h"
#include "showsimg.h"

void setpalette(uint8_t in) {
  uint8_t *palette, data[516];
  uint8_t i, attr;
  int ix;

  if (!opts.palsz && !opts.extra) {
    if (opts.mode==LORES) {
      SETNEXTREG(R_PALCTL, 0x00);
      SETNEXTREG(R_PALIDX, 0);
      pNextReg = R_PALVAL8;
      for(ix=0; ix<256; ix++) pNextDat=ix;
    }
    return;
  }
  errno=0;
  opts.palsz=esx_f_read(in, data, opts.palsz+opts.extra)-opts.extra;
  if (errno) error(errno, "Read Palette", NULL);
  if (opts.extra) {
    palette=&data[1];
    if (opts.mode==HIRES) {
      pTimex=data[0]|0x06;
      attr=0;
    } else {
      attr=data[0];
    }
  } else {
    palette=data;
    attr=0;
  }
  if (attr) {
    SETNEXTREG(R_PALCTL, 0x01);
    SETNEXTREG(R_ULAATTRFMT, attr);
  } else if (opts.layer==LAYER1)
    SETNEXTREG(R_PALCTL, 0x00);
  else
    SETNEXTREG(R_PALCTL, 0x10);
  if (opts.paltype==PALTYPE_ULAPLUS) {
    SETNEXTREG(R_ULACTL, 0x08);
    pULAPlusReg = 0x40;
    SETNEXTREG(R_PALIDX, 0xc0);
    pNextReg = R_PALVAL8;
    for(i=0; i<64 && i<opts.palsz; i++) {
      pULAPlusReg = i;
      pULAPlusDat = palette[i];
    }
  } else {
    SETNEXTREG(R_PALIDX, 0);
    if (opts.palbits==PALBITS_8)
      pNextReg = R_PALVAL8;
    else
      pNextReg = R_PALVAL9;
    if (opts.paltype!=PALTYPE_ULANEXT) {
      for(ix=0; ix<opts.palsz; ix++) pNextDat=palette[ix];
    } else if (attr==0xff) {
      for(ix=0; ix<opts.palsz-1; ix++) pNextDat=palette[ix];
      SETNEXTREG(R_GLBLTRANS, palette[ix]);
    } else {
      if (opts.palbits==PALBITS_8) {
	for(ix=0; ix<attr+1 && ix<opts.palsz; ix++) pNextDat=palette[ix];
	SETNEXTREG(R_PALIDX, 0x80);
	pNextReg = R_PALVAL8; 
	for(ix=0; ix<opts.palsz; ix++) pNextDat=palette[ix];	
      } else {
	for(ix=0; ix<2*attr+2 && ix<opts.palsz; ix++) pNextDat=palette[ix];
	SETNEXTREG(R_PALIDX, 0x80);
	pNextReg = R_PALVAL9; 
      }
      for(; ix<opts.palsz; ix++) pNextDat=palette[ix];	
    }
  }
}

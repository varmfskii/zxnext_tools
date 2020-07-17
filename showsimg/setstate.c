#include "zxnext.h"
#include "showsimg.h"

void setstate(void) {
  switch(opts.mode) {
  case ULA:
    SETNEXTREG(R_SPRTCTL, 0x10);
    SETNEXTREG(R_DISPCTL1, 0x00); 
    break;
  case HICOL:
  case MLT:
  case MC:
    SETNEXTREG(R_SPRTCTL, 0x10);
    SETNEXTREG(R_DISPCTL1, 0x02); 
    break;
  case HIRES:
    SETNEXTREG(R_SPRTCTL, 0x10);
    SETNEXTREG(R_DISPCTL1, 0x06);  
    break;
  case L2_256:
  case NXI:
    SETNEXTREG(R_SPRTCTL, 0x04);
    SETNEXTREG(R_DISPCTL1, 0x80);
    SETNEXTREG(R_L2CTL, 0x00);
    SETNEXTREG(R_L2CLIP, 0);
    pNextDat=255;
    pNextDat=0;
    pNextDat=191;
    break;
  case L2_320:
    SETNEXTREG(R_SPRTCTL, 0x04);
    SETNEXTREG(R_DISPCTL1, 0x80);
    SETNEXTREG(R_L2CTL, 0x10);
    SETNEXTREG(R_CLIPCTL, 0x01);
    SETNEXTREG(R_L2CLIP, 0);
    pNextDat=159;
    pNextDat=0;
    pNextDat=255;
    break;
  case L2_640:
    SETNEXTREG(R_SPRTCTL, 0x04);
    SETNEXTREG(R_DISPCTL1, 0x80);
    SETNEXTREG(R_L2CTL, 0x20);
    SETNEXTREG(R_CLIPCTL, 0x01);
    SETNEXTREG(R_L2CLIP, 0);
    pNextDat=159;
    pNextDat=0;
    pNextDat=255;
    break;
  case LORES:
    SETNEXTREG(R_SPRTCTL, 0x90);
    SETNEXTREG(R_LORESCTL, 0x00);
    break;
  case RAD:
    SETNEXTREG(R_SPRTCTL, 0x90);
    SETNEXTREG(R_LORESCTL, 0x20);
    break;
  }
}

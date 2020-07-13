#include <stdio.h>
#include "zxnext.h"
#include "showsimg.h"

void restorestate(void) {
  int i;
  
  if (!state->valid) return;
  SETNEXTREG(R_PALIDX, 0);
  for(i=0; i<512; i++) SETNEXTREG(R_PALVAL9, state->palette[i]);
  SETNEXTREG(R_PALCTL, state->palctl);
  SETNEXTREG(R_ULAATTRFMT, state->ulaattrfmt);
  SETNEXTREG(R_GLBLTRANS, state->glbltrans);
  SETNEXTREG(R_CLIPCTL, 0x01);
  SETNEXTREG(R_L2CLIP, state->x1);
  pNextDat=state->x2;
  pNextDat=state->y1;
  pNextDat=state->y2;
  SETNEXTREG(R_ULACTL, state->ulactl);
  SETNEXTREG(R_SPRTCTL, state->sprtctl);
  SETNEXTREG(R_LORESCTL, state->loresctl);
  SETNEXTREG(R_L2CTL, state->l2ctl);
  SETNEXTREG(R_DISPCTL1, state->dispctl1);
  pTimex = state->timex;
  SETNEXTREG(R_PER3, state->per3);
  SETNEXTREG(R_MMU5, state->mmu5);
}

void savestate(void) {
  int i, j;
  
  state->mmu5 = GETNEXTREG(R_MMU5);
  state->per3 = GETNEXTREG(R_PER3);
  pNextDat = state->per3 | 0x04; /* enable read on timex port */
  state->timex = pTimex;
  state->dispctl1 = GETNEXTREG(R_DISPCTL1);
  state->l2ctl = GETNEXTREG(R_L2CTL);
  state->loresctl = GETNEXTREG(R_LORESCTL);
  state->sprtctl = GETNEXTREG(R_SPRTCTL);
  SETNEXTREG(R_CLIPCTL, 0x01);
  state->x1 = GETNEXTREG(R_L2CLIP);
  state->x2 = pNextDat;
  state->y1 = pNextDat;
  state->y2 = pNextDat;
  state->ulactl = GETNEXTREG(R_ULACTL);
  state->glbltrans=GETNEXTREG(R_GLBLTRANS);
  state->ulaattrfmt = GETNEXTREG(R_ULAATTRFMT);
  state->palctl = GETNEXTREG(R_PALCTL);
  if ((opts.mode&LAYER)==L1)
    pNextDat = 0x00;
  else
    pNextDat = 0x10;
  for(i=0, j=0; j<256; j++)  {
    SETNEXTREG(R_PALIDX, j);
    state->palette[i++] = GETNEXTREG(R_PALVAL8);
    state->palette[i++] = GETNEXTREG(R_PALVAL9);
  }
  state->valid=1;
}

void setstate(void) {
  switch(opts.mode) {
  case ULA:
    SETNEXTREG(R_SPRTCTL, 0x10);
    SETNEXTREG(R_DISPCTL1, 0x00); 
    break;
  case HICOL:
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

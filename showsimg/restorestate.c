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

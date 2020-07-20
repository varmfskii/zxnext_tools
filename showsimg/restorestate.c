#include "zxnext.h"
#include "showsimg.h"

void restorestate(nextstate_t *old_state) {
  int i;
  
  if (!old_state->valid) return;
  SETNEXTREG(R_PALCTL, (opts.layer==LAYER1)?0x00:0x10);
  SETNEXTREG(R_PALIDX, 0x00);
  for(i=0; i<512; i++) SETNEXTREG(R_PALVAL9, old_state->palette[i]);
  SETNEXTREG(R_PALCTL, old_state->palctl);
  SETNEXTREG(R_ULAATTRFMT, old_state->ulaattrfmt);
  SETNEXTREG(R_GLBLTRANS, old_state->glbltrans);
  SETNEXTREG(R_CLIPCTL, 0x01);
  SETNEXTREG(R_L2CLIP, old_state->x1);
  pNextDat=old_state->x2;
  pNextDat=old_state->y1;
  pNextDat=old_state->y2;
  SETNEXTREG(R_ULACTL, old_state->ulactl);
  SETNEXTREG(R_SPRTCTL, old_state->sprtctl);
  SETNEXTREG(R_LORESCTL, old_state->loresctl);
  SETNEXTREG(R_L2CTL, old_state->l2ctl);
  SETNEXTREG(R_DISPCTL1, old_state->dispctl1);
  pTimex = old_state->timex;
  SETNEXTREG(R_PER3, old_state->per3);
  SETNEXTREG(R_MMU5, old_state->mmu5);
}

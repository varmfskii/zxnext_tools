#include "zxnext.h"
#include "showsimg.h"

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
  if (opts.layer==LAYER1)
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

#include "NexCreator.h"

/* we're ignoring bank at $c000 initially being variable and keeping
   it as 0 as we're creating a large SNA not saving one mid game.
   0,1,2,3,4,5,6,7 */
int bankAdjust[] = { 2,3,1,4,5,0,6,7 };

int getRealBank(int bnk) {
  if (bnk>7) return bnk;
  return bankAdjust[bnk];
}

#include "nexcreator.h"

/* we're ignoring bank at $c000 initially being variable and keeping
   it as 0 as we're creating a large SNA not saving one mid game.
   0,1,2,3,4,5,6,7 */
int nextBank[] = { 1,3,0,4,6,2,7,8 };

int getNextBank(int bnk) {
  if (bnk>7) return bnk + 1;
  return nextBank[bnk];
}

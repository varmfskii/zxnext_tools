#include "NexCreator.h"

int bankOrder[] = { 5,2,0,1,3,4,6,7 };
int getBankOrder(int bnk) {
  if (bnk>7) return bnk;
  return bankOrder[bnk];
}

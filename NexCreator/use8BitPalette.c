#include "NexCreator.h"
#include <string.h>

int use8BitPalette = 0;
unsigned char convert8BitTo3Bits(unsigned char v) {
  int ret = v;//+16;
  if (ret>255) ret = 255;
  ret = ret >> 5;
  return ret;
}

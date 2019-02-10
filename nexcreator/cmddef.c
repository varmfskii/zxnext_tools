#include <stdio.h>
#include "nexcreator.h"

void cmddef(void) {
  char filename[NAMELEN];

  address=0;
  bank=0;
  ptr = inputLine;
  getString(filename, NAMELEN);
  if (ptr[0] == ',') {
    ptr++;
    bank = getInt();
    if (ptr[0] == ',') {
      ptr++;
      address = getHex();
    }
  }
  printf("File '%s' 16K bank %d, %04x\n", filename, bank, address);
  for (int i = 0; i < 8; i++) {
    if (ptr[0] == ',') {
      ptr++;
      SNABank[i] = getInt();
      //printf("SNABank[%d]=%d\n", i, SNABank[i]);
    }
    else break;
  }
  addFile(filename);
}

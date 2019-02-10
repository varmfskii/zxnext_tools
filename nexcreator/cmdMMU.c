#include <stdio.h>
#include "nexcreator.h"

void cmdMMU(void) {
  int bank8k, address8k;
  char filename[NAMELEN];

  address=address8k=0;
  ptr = &inputLine[4];
  getString(filename, NAMELEN);
  if (ptr[0] == ',') {
    ptr++;
    bank8k = getInt();
    bank = bank8k / 2;
    if (ptr[0] == ',') {
      ptr++;
      address = getHex();
      address8k = address;
      if (bank8k != (bank * 2)) address += 0x2000;
    }
    printf("File '%s' 8K bank %d, %04x (16K bank %d, %04x)\n",
	   filename, bank8k, address8k, bank, address);
    addFile(filename);
  }
}

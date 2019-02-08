#include <stdio.h>
#include "nexcreator.h"

void cmdSLR(void) {
  int i;
  FILE *fin2;
  char filename[NAMELEN];
  
  ptr = &inputLine[4];
  getString(filename, NAMELEN);
  fin2 = fopen(filename, "rb");
  if (fin2 != NULL) {
    fread(tempHeader, 1, 0x36, fin2);
    fread(tempPalette, 4, 256, fin2);
    for (i = 0; i < 256; i++) {
      paletteLoRes[i] =
	((convert8BitTo3Bits(tempPalette[i * 4 + 0]) >> 2 & 1) << 8) +
	(convert8BitTo3Bits(tempPalette[i * 4 + 0]) >> 1) +
	(convert8BitTo3Bits(tempPalette[i * 4 + 1]) << 2) +
	(convert8BitTo3Bits(tempPalette[i * 4 + 2]) << 5);
    }
    i = tempHeader[11] * 256 + tempHeader[10];
    fseek(fin2, (long int)i, SEEK_SET);
    for (i = 0; i < 96; i++) {
      if (tempHeader[25] < 128) {
	fread(&loadingLoRes[(95 - i) * 128], 1, 128, fin2);
      } else {
	fread(&loadingLoRes[i * 128], 1, 128, fin2);
      }
    }
    fclose(fin2);
    header512.LoadingScreen |= 4;
    printf("Loading Screen '%s'\n", filename);
    fileadded = 1;
  } else {
    printf("Can't find '%s'\n", filename);
  }
}

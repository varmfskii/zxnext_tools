#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "nexcreator.h"

void cmdXSLR(void) {
  int i, len;
  FILE *fin2;
  char filename[NAMELEN];
  uint8_t buffer[0x3200];
  ptr = &inputLine[5];
  skipSpace();
  getString(filename, NAMELEN);
  if (*ptr == ',') {
    ptr++;
    header512.BorderColour = getInt();
  }
  fin2 = fopen(filename, "rb");
  if (fin2 != NULL) {
    len=fread(buffer, 1, 0x3200, fin2);
    switch (len) {
    case 0x3000:
      /* no palette */
      use8BitPalette=1;
      for(i=0; i<0x100; i++) paletteLoRes[i]=i;
      break;
    case 0x3100:
      /* 8-bit palette */
      use8BitPalette=1;
      for(i=0; i<0x100; i++) paletteLoRes[i]=buffer[i+0x3000];
      break;
    case 0x3200:
      /* 9-bit palette */
      use8BitPalette=0;
      for(i=0; i<0x100; i++) paletteLoRes[i]=(buffer[2*i+0x3001]<<8)|
			       buffer[2*i+0x3000];
      break;
    default:
      fprintf(stderr, "error\n");
      return;
    }
    memcpy(loadingLoRes, buffer, 0x3000);
    fclose(fin2);
    header512.LoadingScreen |= 4 + (dontSavePalette ? 128 : 0);
    printf("Loading Screen '%s'\n", filename);
    fileadded = 1;
  } else {
    printf("Can't find '%s'\n", filename);
  }
}

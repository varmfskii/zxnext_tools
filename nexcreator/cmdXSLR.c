#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "nexcreator.h"

void cmdXSLR(void) {
  int i, len;
  FILE *fin2;
  char filename[NAMELEN];
  uint8_t buffer[0x3200], *scr;
  ptr = &inputLine[4];
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
      scr=buffer;
      use8BitPalette=1;
      for(i=0; i<0x100; i++) paletteLoRes[i]=i;
      break;
    case 0x3100:
      /* 8-bit palette */
      scr=buffer+0x100;
      use8BitPalette=1;
      for(i=0; i<0x100; i++) paletteLoRes[i]=buffer[i];
      break;
    case 0x3200:
      /* 9-bit palette */
      scr=buffer+0x200;
      use8BitPalette=0;
      for(i=0; i<0x100; i++) paletteLoRes[i]=(buffer[2*i+1]<<8)|buffer[2*i];
      break;
    default:
      fprintf(stderr, "error\n");
      return;
    }
    memcpy(loadingLoRes, scr, 0x3000);
    fclose(fin2);
    header512.LoadingScreen |= 4 + (dontSavePalette ? 128 : 0);
    printf("Loading Screen '%s'\n", filename);
    fileadded = 1;
  } else {
    printf("Can't find '%s'\n", filename);
  }
}

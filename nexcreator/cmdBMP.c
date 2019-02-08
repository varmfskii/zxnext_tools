#include <stdio.h>
#include "nexcreator.h"

void cmdBMP(void) {
  int i;
  FILE *fin2;
  char filename[NAMELEN];
  
  ptr = &inputLine[4];
  skipSpace();
  if (*ptr == '!') {
    ptr++;
    dontSavePalette = 1;
  }
  if (*ptr == '8') {
    ptr++;
    use8BitPalette = 1;
    if (*ptr == ',') ptr++;
  }
  getString(filename, NAMELEN);
  if (*ptr == ',') {
    ptr++;
    header512.BorderColour = getInt();
  }
  fin2 = fopen(filename, "rb");
  if (fin2 != NULL) {
    fread(tempHeader, 1, 0x36, fin2);
    fread(tempPalette, 4, 256, fin2);
    for (i = 0; i < 256; i++) {
      palette[i] =
	((convert8BitTo3Bits(tempPalette[i*4+0])>>2&1)<<8)+
	(convert8BitTo3Bits(tempPalette[i*4+0])>>1)+
	(convert8BitTo3Bits(tempPalette[i*4+1])<<2)+
	(convert8BitTo3Bits(tempPalette[i*4+2])<<5);
      if (use8BitPalette) palette[i] &= 0xff;
    }
    i = tempHeader[11] * 256 + tempHeader[10];
    fseek(fin2, (long int)i, SEEK_SET);
    for (i = 0; i < 192; i++) {
      if (tempHeader[25] < 128) {
	fread(&loading[(191 - i) * 256], 1, 256, fin2);
      } else {
	fread(&loading[i * 256], 1, 256, fin2);
      }
    }
    fclose(fin2);
    header512.LoadingScreen |= 1 + (dontSavePalette ? 128 : 0);
    printf("Loading Screen '%s'\n", filename);
    fileadded = 1;
    if (*ptr == ',') {
      ptr++;
      header512.loadingBar = getInt();
      //Loading bar off=0/on=1
      if (*ptr == ',') {
	ptr++;
	header512.loadingColour = getInt();
	//Loading bar Layer2 index colour
	if (*ptr == ',') {
	  ptr++;
	  header512.loadingBankDelay = getInt();
	  //Delay after each bank
	  if (*ptr == ',') {
	    ptr++;
	    header512.loadedDelay = getInt();
	    //Delay (frames) after loading before running
	  }
	}
      }
    }
  }
  if (*ptr == ',') {
    ptr++;
    HiResColour = getInt();
  }
}

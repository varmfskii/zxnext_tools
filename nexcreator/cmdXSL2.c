#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "nexcreator.h"

void cmdXSL2(void) {
  int i, len;
  FILE *fin2;
  char filename[NAMELEN];
  uint8_t buffer[0xc200], *scr;
  ptr = &inputLine[4];
  skipSpace();
  getString(filename, NAMELEN);
  if (*ptr == ',') {
    ptr++;
    header512.BorderColour = getInt();
  }
  fin2 = fopen(filename, "rb");
  if (fin2 != NULL) {
    len=fread(buffer, 1, 0xc200, fin2);
    switch (len) {
    case 0xc000:
      /* no palette */
      scr=buffer;
      dontSavePalette=1;
      break;
    case 0xc100:
      /* 8-bit palette */
      scr=buffer+0x100;
      use8BitPalette=1;
      for(i=0; i<0x100; i++) palette[i]=buffer[i];
      break;
    case 0xc200:
      /* 9-bit palette */
      scr=buffer+0x200;
      use8BitPalette=0;
      for(i=0; i<0x100; i++) palette[i]=(buffer[2*i+1]<<8)|buffer[2*i];
      break;
    default:
      fprintf(stderr, "error\n");
      return;
    }
    memcpy(loading, scr, 0xc000);
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
}

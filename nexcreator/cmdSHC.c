#include <stdio.h>
#include "nexcreator.h"

void cmdSHC(void) {
  FILE *fin2;
  char filename[NAMELEN];
  
  ptr = &inputLine[4];
  getString(filename, NAMELEN);
  fin2 = fopen(filename, "rb");
  if (fin2 != NULL) {
    fread(&loadingHiCol[0], 1, 6144 + 6144, fin2);
    fclose(fin2);
    header512.LoadingScreen |= 16;
    printf("Loading Screen '%s'\n", filename);
    fileadded = 1;
  }
}

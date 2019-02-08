#include <stdio.h>
#include "nexcreator.h"

void cmdSCR(void) {
  FILE *fin2;
  char filename[NAMELEN];
  
  ptr = &inputLine[4];
  getString(filename, NAMELEN);
  fin2 = fopen(filename, "rb");
  if (fin2 != NULL) {
    fread(loadingULA, 1, 6144 + 768, fin2);
    fclose(fin2);
    header512.LoadingScreen |= 2;
    printf("Loading Screen '%s'\n", filename);
    fileadded = 1;
  } else {
    printf("Can't find '%s'\n", filename);
  }
}

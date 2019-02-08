#include <stdio.h>
#include "nexcreator.h"

void cmdSHR(void) {
  FILE *fin2;
  char filename[NAMELEN];
  
  ptr = &inputLine[4];
  getString(filename, NAMELEN);
  fin2 = fopen(filename, "rb");
  if (fin2 != NULL) {
    fread(&loadingHiRes[0], 1, 6144 + 6144, fin2);
    fclose(fin2);
    header512.LoadingScreen |= 8;
    printf("Loading Screen '%s'\n", filename);
    fileadded = 1;
    if (ptr[0] == ',') {
      header512.HiResColours = getInt();
    }
  } else {
    printf("Can't find '%s'\n", filename);
  }
}

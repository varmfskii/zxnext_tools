#include <stdio.h>
#include "nexcreator.h"

void cmdCOR(void) {
  ptr = &inputLine[4];
  header512.CoreRequired[CORE_MAJOR] = getInt();
  //Loading bar off=0/on=1
  if (ptr[0] == ',') {
    ptr++;
    header512.CoreRequired[CORE_MINOR] = getInt();
    //Loading bar Layer2 index colour
    if (ptr[0] == ',') {
      ptr++;
      header512.CoreRequired[CORE_SUBMINOR] = getInt();
      //Delay after each bank
    }
  }
  printf("Requires Core %d,%d,%d or greater\n",
	 header512.CoreRequired[CORE_MAJOR],
	 header512.CoreRequired[CORE_MINOR],
	 header512.CoreRequired[CORE_SUBMINOR]);
}

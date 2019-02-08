#include <stdio.h>
#include <string.h>
#include "nexcreator.h"

void cmdPCSP(void) {
  ptr = &inputLine[5];
  header512.PC = getInt();
  printf("PC=$%04x\n", header512.PC);
  if (ptr[0] == ',') {
    ptr++;
    header512.SP = getInt();
    printf("SP=$%04x\n", header512.SP);
    if (ptr[0] == ',') {
      ptr++;
      // This is a v1.2+ feature. Version number is only incremented if this token is parsed and the bank is > 0
      header512.EntryBank = getInt();
      if (header512.EntryBank > 0 && versionDecimal < 12) {
	versionDecimal = 12;
	memcpy(header512.VersionNumber, "V1.2", 4);
	printf("Entry Bank=%d\n", header512.EntryBank);
      }
    }
  }
}

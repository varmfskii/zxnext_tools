#include <string.h>
#include "nexcreator.h"

void addFile(char *fname) {
  FILE *fin2;
  int bank, address;
  int sna = 0;
  
  if (strlen(fname)<3) return;
  fin2 = fopen(fname, "rb");
  if (fin2 == NULL) {
    printf("Can't open '%s'\n", fname);
    return;
  }
  if ((fname[strlen(fname) - 3] & 0xdf) == 'S') {
    if ((fname[strlen(fname) - 2] & 0xdf) == 'N') {
      if ((fname[strlen(fname) - 1] & 0xdf) == 'A') {
	fread(SNAHeader, 1, 27, fin2);
	bank = 5;
	address = 0x4000;
	sna = 1;
      }
    }
  }
  while (!feof(fin2)) {
      int realBank = getRealBank(bank);
      long len = fread(&bigFile[realBank * 16384 + (address & 0x3fff)], 1, 0x4000 - (address & 0x3fff), fin2);
      if (len == 0) continue;
      if (bank<64 + 48) {
	header512.Banks[bank] = 1;
      }
      if (sna == 1 && SNABank[realBank] == 0) {
	header512.Banks[bank] = 0;
	printf("Skipping SNA bank %d\n", bank);
      } else
	printf("bank=%d,addr=%04x,realbank=%d,%ld\n", bank, address, realBank, len);
      if (realBank>lastBank) lastBank = realBank;
      if (sna == 1) {
	if (bank == 0) {
	  len = fread(&SNA128Header, 1, 4, fin2);
	  printf("128KHeader len = %ld\n", len);
	  int sp = (SNAHeader[23] + 256 * SNAHeader[24]);
	  if (len == 0) {
	    int sp2 = sp;
	    if (sp2 >= 16384) sp2 -= 16384;
	    SNA128Header[0] = bigFile[sp2 + 16];
	    SNA128Header[1] = bigFile[sp2 + 17];
	    SNA128Header[2] = 0;
	    SNA128Header[3] = 0;
	  }
	  header512.SP = sp;
	  header512.PC = SNA128Header[0] + 256 * SNA128Header[1];
	  printf("SP=%04x,PC=%04x\n", header512.SP, header512.PC);
	}
      }
      address = ((address & 0xc000) + 0x4000) & 0xc000;
      bank = getNextBank(bank);
  }
  fclose(fin2);
}

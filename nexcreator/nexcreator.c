#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nexcreator.h"

FILE *fin1;
FILE *fin2;
FILE *fout;
int line = 0;
char *ptr = NULL;
int lastBank = -1;
long long filelen;
int fileadded = 0;
int versionDecimal = 11; // 11 = 1.1, 12 = 1.2, etc

HEADER header512 = {
    "Next",
    "V1.1",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    { 0 },
    0,
    0,
    0,
    0,
    0,
    { 0,0,0 },
    0,
    0
};

EXTRAFILE extrafiles[65536];		// enough room for 65536 extra files
unsigned char tempHeader[0x36];
unsigned char tempPalette[256 * 4];
unsigned char dontSavePalette = 0;
unsigned short palette[256];
unsigned char loading[49152];
unsigned char loadingULA[6144 + 768 + 256];
unsigned short paletteLoRes[256];
unsigned char loadingLoRes[6144 + 6144];
unsigned char loadingHiRes[6144 + 6144 + 768 + 256];
unsigned char loadingHiCol[6144 + 6144];
int HiResColour = 0;
unsigned char bigFile[1024 * 1024 * 1024];
unsigned char temp16k[16384];
char inputLine[4096];
char filename[NAMELEN];
unsigned char SNAHeader[27];
unsigned char SNA128Header[4] = { 0,0,0,0 };
unsigned char SNABank[8] = { 1,1,1,1,1,1,1,1 };
int bank, address;

int main(int c, char **s) {
  int i;
  
  if (c != 3) {
    printf("Nex File Creator\nUsage :- \nNexCreator source.txt dest.big\n\n");
    return(1);
  }
  fin1 = fopen(s[1], "rt");
  if (fin1 == NULL) {
    printf("Can't open '%s'\n", s[1]);
    return(1);
  }
  line = 0;
  while (!feof(fin1)) {
    memset(inputLine, 0, sizeof(inputLine));
    fgets(inputLine, sizeof(inputLine), fin1);
    if (strlen(inputLine)>0) {
      if (inputLine[strlen(inputLine) - 1] == 10)
	inputLine[strlen(inputLine) - 1] = 0;
      if (strlen(inputLine)>0) {
	if (inputLine[strlen(inputLine) - 1] == 13)
	  inputLine[strlen(inputLine) - 1] = 0;
      }
    }
    line++;
    if (inputLine[0] == '!') {
      switch (getcommand(inputLine)) {
      case BANK:
	cmdBANK();
      case BMP:
	cmdBMP();
	break;
      case COR:
	cmdCOR();
	break;
      case PCSP:
	cmdPCSP();
	break;
      case XSLR:
	cmdXSLR();
	break;
      case SCR:
	cmdSCR();
	break;
      case SHC:
	cmdSHC();
	break;
      case SHR:
	cmdSHR();
	break;
      case XSL2:
	cmdXSL2();
	break;
      case SLR:
	cmdSLR();
	break;
      case MMU:
	cmdMMU();
	break;
      default:
	printf("Unknown command: %s\n", inputLine);
	return 1;
      }
    } else if (inputLine[0] != ';' && inputLine[0] != 0) {
      cmddef();
    }
    //pintf("line %d='%s'\n",line,inputLine);
  }
  fclose(fin1);
  if ((lastBank>-1) || (fileadded != 0)) {
    printf("Generating NEX file in %s format\n", header512.VersionNumber);
    for (i = 0; i < 64 + 48; i++) {
      if (header512.Banks[i] > 0) header512.NumBanksToLoad++;
      if (i >= 48) header512.RAM_Required = 1;
    }
    fout = fopen(s[2], "wb");
    if (fout == NULL) {
      printf("Can't open '%s'\n", s[2]);
      return(1);
    }
    fwrite(&header512, 1, 512, fout);
    if (header512.LoadingScreen) {
      if (header512.LoadingScreen & 1) {
	if (!(header512.LoadingScreen & 128)) fwrite(palette, 2, 256, fout);
	fwrite(loading, 256, 192, fout);
      }
      if (header512.LoadingScreen & 2) {
	fwrite(loadingULA, 1, 6144 + 768, fout);
      }
      if (header512.LoadingScreen & 4) {
	if (!(header512.LoadingScreen & 128))
	  fwrite(paletteLoRes, 2, 256, fout);
	fwrite(loadingLoRes, 1, 6144 + 6144, fout);
      }
      if (header512.LoadingScreen & 8) {
	fwrite(loadingHiRes, 1, 6144 + 6144, fout);
      }
      if (header512.LoadingScreen & 16) {
	fwrite(loadingHiCol, 1, 6144 + 6144, fout);
      }
    }
    for (i = 0; i<112; i++) {
      if (header512.Banks[getBankOrder(i)]) {
	fwrite(&bigFile[i * 16384], 1, 16384, fout);
      }
    }
    fclose(fout);
  }
}

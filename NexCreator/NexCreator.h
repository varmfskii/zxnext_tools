#ifndef NEXCREATOR_H
#define NEXCREATOR_H

#include <stdio.h>

#define CORE_MAJOR	0
#define CORE_MINOR	1
#define CORE_SUBMINOR	2

typedef struct {
  char Next[4];
  //"Next"
  char VersionNumber[4];
  //"V1.1" = Gold distro. V1.2 allows entering with PC in a 16K bank >= 8.
  unsigned char RAM_Required;
  //0=768K, 1=1792K
  unsigned char NumBanksToLoad;
  //0-112 x 16K banks
  unsigned char LoadingScreen;
  /* 1 = layer2 at 16K page 9, 2=ULA loading, 4=LORES, 8=HiRes,
     16=HIColour, +128 = don't load palette. */
  unsigned char BorderColour;
  //0-7 ld a,BorderColour:out(254),a
  unsigned short SP;
  //Stack Pointer
  unsigned short PC;
  //Code Entry Point : $0000 = Don't run just load.
  unsigned short NumExtraFiles;
  //NumExtraFiles
  unsigned char Banks[64 + 48];
  /* Which 16K Banks load. : Bank 5 = $0000-$3fff, Bank 2 =
     $4000-$7fff, Bank 0 = $c000-$ffff */
  unsigned char loadingBar;
  //Loading bar off=0/on=1
  unsigned char loadingColour;
  //Loading bar Layer2 index colour
  unsigned char loadingBankDelay;
  //Delay after each bank
  unsigned char loadedDelay;
  //Delay (frames) after loading before running
  unsigned char dontResetRegs;
  //Don't reset the registers
  unsigned char CoreRequired[3];
  /* CoreRequired byte per value, decimal, not
     string. ordering... Major, Minor, Subminor */
  unsigned char HiResColours;
  /* to be anded with three, and shifted left three times, and add the
     mode number for hires and out (255),a */
  unsigned char EntryBank;
  /* V1.2: 0-112, this 16K bank will be paged in at $C000 before
     jumping to PC. The default is 0, which is the default upper 16K
     bank anyway. */
  unsigned char RestOf512Bytes[512-(4+4+1+1+1+1+2+2+2+64+48+1+1+1+1+1+3+1+1)];
} HEADER;

typedef struct {
  unsigned char filename[64-8];
  unsigned int offset;
  unsigned int length;
} EXTRAFILE;

extern EXTRAFILE extrafiles[];
extern FILE *fin1, *fin2, *fout;
extern HEADER header512;
extern char *ptr;
extern char filename[], inputLine[];
extern int HiResColour, fileadded, palcnt, versionDecimal, use8BitPalette;
extern int line, filecount, bank, lastBank, address;
extern int bankAdjust[], bankOrder[], nextBank[];
extern long long filelen;
extern unsigned char SNA128Header[], SNABank[], SNAHeader[], bigFile[];
extern unsigned char dontSavePalette, loadingHiCol[];
extern unsigned char loadingHiRes[], loadingLoRes[], loadingULA[], loading[];
extern unsigned char temp16k[], tempHeader[], tempPalette[];
extern unsigned short paletteLoRes[], palette[];

int getHex();
void skipSpace();
void getString(char *dst, int maxlen);
int getInt();
int getRealBank(int bnk);
int getBankOrder(int bnk);
int getNextBank(int bnk);
void addFile(char *fname);
unsigned char convert8BitTo3Bits(unsigned char v);
#endif

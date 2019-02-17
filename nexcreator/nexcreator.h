#ifndef NEXCREATOR_H
#define NEXCREATOR_H

#include <stdio.h>
#include <stdint.h>

#define CORE_MAJOR	0
#define CORE_MINOR	1
#define CORE_SUBMINOR	2
#define NAMELEN 1024
#define COMMANDS { "!BANK", "!BMP", "!COR", "!MMU", "!PCSP", "!SCR", \
		   "!SHC", "!SHR", "!SL2", "!SLR", NULL }
#define BANK 1
#define BMP 2
#define COR 3
#define MMU 4
#define PCSP 5
#define SCR 6
#define SHC 7
#define SHR 8
#define SL2 9
#define SLR 10

typedef struct {
  char Next[4];
  //"Next"
  char VersionNumber[4];
  //"V1.1" = Gold distro. V1.2 allows entering with PC in a 16K bank >= 8.
  uint8_t RAM_Required;
  //0=768K, 1=1792K
  uint8_t NumBanksToLoad;
  //0-112 x 16K banks
  uint8_t LoadingScreen;
  /* 1 = layer2 at 16K page 9, 2=ULA loading, 4=LORES, 8=HiRes,
     16=HIColour, +128 = don't load palette. */
  uint8_t BorderColour;
  //0-7 ld a,BorderColour:out(254),a
  unsigned short SP;
  //Stack Pointer
  unsigned short PC;
  //Code Entry Point : $0000 = Don't run just load.
  unsigned short NumExtraFiles;
  //NumExtraFiles
  uint8_t Banks[64 + 48];
  /* Which 16K Banks load. : Bank 5 = $0000-$3fff, Bank 2 =
     $4000-$7fff, Bank 0 = $c000-$ffff */
  uint8_t loadingBar;
  //Loading bar off=0/on=1
  uint8_t loadingColour;
  //Loading bar Layer2 index colour
  uint8_t loadingBankDelay;
  //Delay after each bank
  uint8_t loadedDelay;
  //Delay (frames) after loading before running
  uint8_t dontResetRegs;
  //Don't reset the registers
  uint8_t CoreRequired[3];
  /* CoreRequired byte per value, decimal, not
     string. ordering... Major, Minor, Subminor */
  uint8_t HiResColours;
  /* to be anded with three, and shifted left three times, and add the
     mode number for hires and out (255),a */
  uint8_t EntryBank;
  /* V1.2: 0-112, this 16K bank will be paged in at $C000 before
     jumping to PC. The default is 0, which is the default upper 16K
     bank anyway. */
  uint8_t RestOf512Bytes[512-(4+4+1+1+1+1+2+2+2+64+48+1+1+1+1+1+3+1+1)];
} HEADER;

typedef struct {
  uint8_t filename[64-8];
  unsigned int offset;
  unsigned int length;
} EXTRAFILE;

extern HEADER header512;
extern char *ptr;
extern char inputLine[];
extern int HiResColour, fileadded, versionDecimal, use8BitPalette;
extern int lastBank, bank, address;
// end of checked globals
extern int bankAdjust[], bankOrder[], nextBank[];
extern long long filelen;
extern uint8_t SNA128Header[], SNABank[], SNAHeader[], bigFile[];
extern uint8_t dontSavePalette, loadingHiCol[];
extern uint8_t loadingHiRes[], loadingLoRes[], loadingULA[], loading[];
extern uint8_t temp16k[], tempHeader[], tempPalette[];
extern unsigned short paletteLoRes[], palette[];

char *readline(FILE *in);
char **parseCSV(char *line);
int getcommand(char *line);
int getBankOrder(int bnk);
int getHex();
int getInt();
int getNextBank(int bnk);
int getRealBank(int bnk);
uint8_t convert8BitTo3Bits(uint8_t v);
void addFile(char *fname);
void cmdBANK(void);
void cmdBMP(void);
void cmdCOR(void);
void cmdMMU(void);
void cmdPCSP(void);
void cmdSCR(void);
void cmdSHC(void);
void cmdSHR(void);
void cmdSL2(void);
void cmdSLR(void);
void cmddef(void);
void getString(char *dst, int maxlen);
void skipSpace();
#endif

#ifndef SHOW_H
#define SHOW_H

#include <stdint.h>

/* modes */
#define UNKNOWN 0
#define ULAP 0x10
#define TIMEX 0x20
#define L2P 0x40
#define ULA 0x31
#define HICOL 0x32
#define HIRES 0x33
#define L2_256 0x41
#define L2_320 0x42
#define L2_640 0x43
#define LORES 0x51
#define RAD 0x52

#define L2PAGE 18

#define GETNEXTREG(R) (pNextReg=(R), pNextDat)
#define SETNEXTREG(R, V) (pNextReg=(R), pNextDat=(V))

typedef struct nextstate_t {
  uint8_t valid;
  uint8_t mmu5, timex;
  uint8_t per3, ulactl, ulaattrfmt, glbltrans, palctl, dispctl1;
  uint8_t l2ctl, loresctl, sprtctl, x1, x2, y1, y2;
  uint8_t palette[512];
} nextstate_t;

typedef struct opt_t {
  uint8_t mode, palbits, ulaplus, autoexit;
  uint16_t size;
} opt_t;

char *getext(char *name);
char *getopts(int argc, char *argv[]);
char *string32(int32_t num);
void error(uint8_t errno, char *s1, char *s2);
void guessmode(uint32_t size, char *name);
void help(void);
void restorestate(void);
void savestate(void);
void setimage(uint8_t in);
void setpalette(uint8_t in);
void setstate(void);

extern nextstate_t *state;
extern opt_t opts;
#endif

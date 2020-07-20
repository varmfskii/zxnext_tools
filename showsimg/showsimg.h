#ifndef SHOW_H
#define SHOW_H

#include <stdint.h>

/* modes */
#define UNK    0
#define ULA    1  /* .scr */
#define HICOL  2  /* .shc */
#define HIRES  3  /* .shr */
#define L2_256 4  /* .sl2 */
#define L2_320 5  /* .sl2 */
#define L2_640 6  /* .sl2 */
#define LORES  7  /* .slr */
#define RAD    8  /* .slr */
#define NXI    9  /* .nxi */
#define MC     10 /* .mc */
#define MLT    11 /* .mlt */

/* palbits */
#define PALBITS_8 0
#define PALBITS_9 1
/* paltype */
#define PALTYPE_NONE 0
#define PALTYPE_ULAPLUS 1
#define PALTYPE_ULANEXT 2
#define PALTYPE_NORM 3
/* layer */
#define LAYER1 0
#define LAYER2 1
/* partord */
#define IEP 0
#define PEI 1
/* data order */
#define ORD_NATIVE 0
#define ORD_NORMAL 1

/* palstyle */
#define PALSTYLE_ULA 0
#define PALSTYLE_1 1
#define PALSTYLE_4 2
#define PALSTYLE_8 3

#define L2PAGE  18
#define ULAPAGE 10

#define GETNEXTREG(R) (pNextReg=(R), pNextDat)
#define SETNEXTREG(R, V) (pNextReg=(R), pNextDat=(V))

typedef struct fmtdesc_t {
  uint32_t imgsz;
} fmtdesc_t;

typedef struct nextstate_t {
  uint8_t palette[512];
  uint8_t mmu5, timex;
  uint8_t per3, ulactl, ulaattrfmt, glbltrans, palctl, dispctl1;
  uint8_t l2ctl, loresctl, sprtctl, x1, x2, y1, y2;
  uint8_t valid:1;
} nextstate_t;

typedef struct opt_t {
  char *name;
  uint8_t mode;
  uint32_t imgsz, palsz;
  unsigned int extra:1, autoexit:1, info:1, sread:1, swrite:1;
  union {
    uint8_t desc;
    struct {
      unsigned int paltype:2, palbits:1;
      unsigned int layer:1, partord:1, pixord:1, attrord:1;
    };
  };
} opt_t;

char *getext(char *name);
char *string32(int32_t num);
void error(uint8_t errno, char *s1, char *s2);
void getopts(int argc, char *argv[]);
void help(void);
void info(void);
void noattr(void);
void readstate(void);
void remap(void);
void restorestate(nextstate_t *s);
void savestate(void);
void setimage(uint8_t in);
void setpalette(uint8_t in);
void setstate(void);
void writestate(void);

extern nextstate_t *state;
extern opt_t opts;
#endif

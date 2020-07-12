#ifndef SHOW_H
#define SHOW_H

#include <stdint.h>

/* modes */
#define LAYER  0x01 /* layer mask */
#define L1     0x00
#define L2     0x01
#define XRES   0x0E /* X-resolution mask */
#define X256   0x00
#define X256A  0x02 /* special value for Timex Hi-Color */
#define X512   0x04
#define X128   0x06
#define X320   0x08
#define X640   0x0A
#define DEPTH  0x30 /* bits per pixel mask */
#define DATTR  0x00
#define D1     0x10
#define D4     0x20
#define D8     0x30
#define ORDER  0x40
#define IEP    0x00
#define EPI    0x40
#define ULA    (L1|X256|DATTR)  /* .scr */
#define HICOL  (L1|X256A|DATTR) /* .shc */
#define HIRES  (L2|X512|D1)     /* .shr */
#define L2_256 (L2|X256|D8)     /* .sl2 */
#define L2_320 (L2|X320|D8)     /* .sl2 */
#define L2_640 (L2|X640|D4)     /* .sl2 */
#define LORES  (L1|X128|D8)     /* .slr */
#define RAD    (L1|X128|D4)     /* .slr */
#define NXI    (L2_256|EPI)     /* .nxi */

#define UNKNOWN 0xff

/* palette types */
#define PTYPE   0x03 /* palette type mask */
#define PNORM   0x00
#define ULAPLUS 0x01
#define ULANEXT 0x02
#define PDEPTH  0x0C /* palette bits per colour */
#define PNONE   0x00
#define P8      0x04
#define P9      0x08

#define L2PAGE  18
#define ULAPAGE 10

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
  char *name, *ext;
  uint8_t mode, palette, extra, autoexit, info;
  uint32_t size;
} opt_t;

char *getext(char *name);
void getopts(int argc, char *argv[]);
char *string32(int32_t num);
void error(uint8_t errno, char *s1, char *s2);
void help(void);
void restorestate(void);
void savestate(void);
void setimage(uint8_t in);
void setpalette(uint8_t in);
void setstate(void);
void info(void);

extern nextstate_t *state;
extern opt_t opts;
#endif

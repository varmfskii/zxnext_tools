#include <stdio.h>
#include <stdlib.h>
#include "showsimg.h"

static char num[12];

void error(uint8_t errno, char *s1, char *s2) {
  restorestate();
  puts("Error");
  if (s1) {
    for(; *s1; s1++) putchar(*s1);
    if (s2) {
      putchar(' ');
      for(; *s2; s2++) putchar(*s2);
    }
  }
  putchar('\n');
  exit(errno);
}

void help(void) {
  puts(".showsimg 1.01.00 Beta");
  puts("Usage: .showsimg [<options>] <filename>");
  puts("options:");
  puts("\t-2: Layer 2 256x192x8");
  puts("\t-3: Layer 2 320x256x8");
  puts("\t-6: Layer 2 640x256x4");
  puts("\t-R: Radastan 128x96x4");
#ifdef DEBUG
  puts("\t-i: Information about image");
#endif
  puts("\t-l: LoRes 128x96x8");
  puts("\t-r: Timex HiRes 512x192x1");
  puts("\t-c: Timex HiCol 256x192/8x1");
  puts("\t-u: ULA 256x192/8x8");
  puts("\t-x: Do not wait, do not restore");
}

char *string32(int32_t n) {
  uint8_t neg, i;

  neg=n<0;
  if (neg) n=-n;
  i=11;
  num[i]='\0';
  do {
    num[--i]=n%10+'0';
    n/=10;
  } while (n);
  if (neg) num[--i]='-';
  return num+i;
}

#ifdef DEBUG
void info(void) {
  puts(opts.name);
  switch(opts.mode) {
  case ULA:
    puts("ULA");
    break;
  case HICOL:
    puts("High Color");
    break;
  case HIRES:
    puts("High Resolution");
    break;
  case L2_256:
    puts("Layer 2 256x192x8");
    break;
  case L2_320:
    puts("Layer 2 320x256x8");
    break;
  case L2_640:
    puts("Layer 2 640x256x4");
    break;
  case LORES:
    puts("Low Resolution 128x96x8");
    break;
  case RAD:
    puts("Radistan 128x96x4");
    break;
  default:
    puts("Unknown");
  }
  if ((opts.mode&LAYER)==L1)
    puts("Layer 1");
  else
    puts("Layer 2");
  if ((opts.mode&XRES)==X128)
    puts("X=128");
  else if ((opts.mode&XRES)==X256)
    puts("X=256");
  else if ((opts.mode&XRES)==X256A)
    puts("X=256+");
  else if ((opts.mode&XRES)==X320)
    puts("X=320");
  else if ((opts.mode&XRES)==X512)
    puts("X=512");
  else if ((opts.mode&XRES)==X640)
    puts("X=640");
  if ((opts.mode&DEPTH)==DATTR)
    puts("ULA Attributes");
  else if ((opts.mode&DEPTH)==D1)
    puts("1 BPP");
  else if ((opts.mode&DEPTH)==D4)
    puts("4 BPP");
  else if ((opts.mode&DEPTH)==D8)
    puts("8 BPP");
  if ((opts.palette&PTYPE)==PNORM)
      puts("Normal Palette");
  else if ((opts.palette&PTYPE)==ULAPLUS)
    puts("ULAplus");
  else if ((opts.palette&PTYPE)==ULANEXT)
    puts("ULANext");
  if ((opts.palette&PDEPTH)==PNONE)
    puts("No Palette");
  else if ((opts.palette&PDEPTH)==P8)
    puts("8-bit palette");
  else if ((opts.palette&PDEPTH)==P9)
    puts("9-bit palette");
  exit(1);
}
#endif

char *getext(char *name) {
  char *ext=NULL;

  for(; *name; name++)
    if (*name=='.') ext=name;
  if (!ext) ext=name;
  return ext;
}

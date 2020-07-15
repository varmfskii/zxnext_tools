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
  puts(".showsimg 1.03.00");
  puts("Theodore (Alex) Evans 2020");
  puts("Usage: .showsimg [<options>] <filename>");
  puts("options:");
  puts("\t-2: Layer 2 256x192x8");
  puts("\t-3: Layer 2 320x256x8");
  puts("\t-6: Layer 2 640x256x4");
  puts("\t-R: Radastan 128x96x4");
  puts("\t-M: MLT HiColor");
  puts("\t-c: Timex HiCol 256x192/8x1");
  puts("\t-h: This help");
#ifdef DEBUG
  puts("\t-i: Information about image");
#endif
  puts("\t-l: LoRes 128x96x8");
  puts("\t-m: MC HiColor");
  puts("\t-n: NXI Layer 2");
  puts("\t-r: Timex HiRes 512x192x1");
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
  if (opts.paltype==PALTYPE_NONE)
    puts("No palette");
  else if (opts.paltype==PALTYPE_ULAPLUS)
    puts("ULAplus");
  else if (opts.paltype==PALTYPE_ULANEXT)
    puts("ULANext");
  else
    puts("Normal Palette");
  if (opts.palbits==PALBITS_8)
    puts("8-bit palette entries");
  else
    puts("9-bit palette entries");
  if (opts.layer==LAYER1)
    puts("Layer 1");
  else
    puts("Layer 2");
  if (opts.partord==IEP)
    puts("IEP");
  else
    puts("PEI");
  if (opts.pixord==ORD_NATIVE)
    puts("Pixels Native Order");
  else
    puts("Pixels Normal Order");
  if (opts.attrord==ORD_NATIVE)
    puts("Attributes Native Order");
  else
    puts("Attributes Normal Order");
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

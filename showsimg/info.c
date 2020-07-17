#include <stdio.h>
#include <stdlib.h>
#include "showsimg.h"

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

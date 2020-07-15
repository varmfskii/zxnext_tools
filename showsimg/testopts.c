#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "showsimg.h"

int main() {
  opt_t opts;
  uint8_t palstyle;
  char const *label;

  puts("Test opts");
  for(opts.mode=0; opts.mode<12; opts.mode++) {
    opts.desc=0;
    switch(opts.mode) {
    case RAD:
      label="RAD";
      palstyle=PALSTYLE_4;
      opts.imgsz=6144;
      opts.layer=LAYER1;
      opts.partord=IEP;
      opts.pixord=ORD_NATIVE;
      opts.attrord=ORD_NATIVE;
      break;
    case ULA:
      label="ULA";
      palstyle=PALSTYLE_ULA;
      opts.imgsz=6912;
      opts.layer=LAYER1;
      opts.partord=IEP;
      opts.pixord=ORD_NATIVE;
      opts.attrord=ORD_NATIVE;
      break;
    case HIRES:
      label="HIRES";
      palstyle=PALSTYLE_1;
      opts.imgsz=12288;
      opts.layer=LAYER1;
      opts.partord=IEP;
      opts.pixord=ORD_NATIVE;
      opts.attrord=ORD_NATIVE;
      break;
    case HICOL:
      label="HICOL";
      palstyle=PALSTYLE_ULA;
      opts.imgsz=12288;
      opts.layer=LAYER1;
      opts.partord=IEP;
      opts.pixord=ORD_NATIVE;
      opts.attrord=ORD_NATIVE;
      break;
    case MC:
      label="MC";
      palstyle=PALSTYLE_ULA;
      opts.imgsz=12288;
      opts.layer=LAYER1;
      opts.partord=IEP;
      opts.pixord=ORD_NATIVE;
      opts.attrord=ORD_NORMAL;
      break;
    case MLT:
      label="MLT";
      palstyle=PALSTYLE_ULA;
      opts.imgsz=12288;
      opts.layer=LAYER1;
      opts.partord=IEP;
      opts.pixord=ORD_NORMAL;
      opts.attrord=ORD_NORMAL;
      break;
    case LORES:
      label="LORES";
      palstyle=PALSTYLE_8;
      opts.imgsz=12288;
      opts.layer=LAYER1;
      opts.partord=IEP;
      opts.pixord=ORD_NATIVE;
      opts.attrord=ORD_NATIVE;
      break;
    case L2_256:
      label="L2_256";
      palstyle=PALSTYLE_8;
      opts.imgsz=49152l;
      opts.layer=LAYER2;
      opts.partord=IEP;
      opts.pixord=ORD_NATIVE;
      opts.attrord=ORD_NATIVE;
      break;
    case NXI:
      label="NXI";
      palstyle=PALSTYLE_8;
      opts.imgsz=49152l;
      opts.layer=LAYER2;
      opts.partord=PEI;
      opts.pixord=ORD_NATIVE;
      opts.attrord=ORD_NATIVE;
      break;
    case L2_320:
      label="L2_320";
      palstyle=PALSTYLE_8;
      opts.imgsz=81920l;
      opts.layer=LAYER2;
      opts.partord=IEP;
      opts.pixord=ORD_NATIVE;
      opts.attrord=ORD_NATIVE;
      break;
    case L2_640:
      label="L2_640";
      palstyle=PALSTYLE_4;
      opts.imgsz=81920l;
      opts.layer=LAYER2;
      opts.partord=IEP;
      opts.pixord=ORD_NATIVE;
      opts.attrord=ORD_NATIVE;
      break;
    default:
      label="UNK";
      opts.desc=0x00;
    }
    printf("%s: %02x\n", label, opts.desc);
  }
  opts.desc=0x00;
  opts.paltype=PALTYPE_NONE;
  printf("PALTYPE_NONE %02x\n", opts.desc);
  opts.desc=0x00;
  opts.paltype=PALTYPE_ULAPLUS;
  printf("PALTYPE_ULAPLUS %02x\n", opts.desc);
  opts.desc=0x00;
  opts.paltype=PALTYPE_ULANEXT;
  printf("PALTYPE_ULANEXT %02x\n", opts.desc);
  opts.desc=0x00;
  opts.paltype=PALTYPE_NORM;
  printf("PALTYPE_NORM %02x\n", opts.desc);
  opts.desc=0x00;
  opts.palbits=PALBITS_8;
  printf("PALBITS_8 %02x\n", opts.desc);
  opts.desc=0x00;
  opts.palbits=PALBITS_9;
  printf("PALBITS_9 %02x\n", opts.desc);
  for(;;);
  return 0;
}


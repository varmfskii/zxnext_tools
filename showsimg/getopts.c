#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "showsimg.h"

void getopts(int argc, char *argv[]) {
  uint8_t i, j, palstyle;
  uint32_t fsize;
  struct esx_stat stat;
  char *ext;
  
  opts.name=NULL;
  ext=NULL;
  opts.mode=UNK;
  opts.autoexit=0;
  opts.sread=0;
  opts.swrite=0;
  opts.info=0;
  palstyle=PALSTYLE_ULA;
  for(i=1; i<argc; i++){
    if (argv[i][0]=='-') { //options
      for(j=1; argv[i][j]; j++) {
	switch(argv[i][j]) {
	case '2':
	  opts.mode = L2_256;
	  break;
	case '3':
	  opts.mode = L2_320;
	  break;
	case '6':
	  opts.mode = L2_640;
	  break;
	case 'M':
	  opts.mode = MLT;
	  break;
	case 'R':
	  opts.mode = RAD;
	  break;
	case 'S':
	  opts.swrite = 1;
	  break;
	case 'c':
	  opts.mode = HICOL;
	  break;
	case 'h':
	  help();
	  exit(0);
	case 'i':
	  opts.info=1;
	  break;
	case 'l':
	  opts.mode = LORES;
	  break;
	case 'm':
	  opts.mode=MC;
	  break;
	case 'n':
	  opts.mode = NXI;
	  break;
	case 'r':
	  opts.mode = HIRES;
	  break;
	case 's':
	  opts.sread = 1;
	  break;
	case 'u':
	  opts.mode = ULA;
	  break;
	case 'x':
	  opts.autoexit = 1;
	  break;
	case '8':
	case '9':
	case '+':
	  break;
	default:
	  help();
	  error(7, "Unknown option", NULL);
	}
      }
    } else {
      opts.name = argv[i];
      ext = getext(opts.name);
    }
  }
  if (!opts.name) {
    if (opts.swrite) {
      opts.layer=LAYER1;
      writestate();
      opts.layer=LAYER2;
      writestate();
      puts("State saved");
      exit(0);
    } else if (opts.sread) {
      opts.layer=LAYER1;
      readstate();
      opts.layer=LAYER2;
      readstate();
      puts("state restored");
      exit(0);
    } else {
      help();
      error(7, "Bad command", NULL);
    }
  }
  if (esx_f_stat(opts.name, &stat)==0xff)
    error(errno, "Unable to stat:", opts.name);
  fsize=stat.size;
  if (opts.mode==UNK) {
    if (!strcmp(ext, ".scr")) {
      opts.mode=ULA;
    } else if (!strcmp(ext, ".shc")) {
      opts.mode=HICOL;
    } else if (!strcmp(ext, ".shr")) {
      opts.mode=HIRES;
    } else if (!strcmp(ext, ".sl2")) {
      if (fsize==81920l || fsize>81952l)
	opts.mode=L2_320;
      else if (fsize>81920l)
	opts.mode=L2_640;
      else
	opts.mode=L2_256;
    } else if (!strcmp(ext, ".slr")) {
      if (fsize>=12288)
	opts.mode=LORES;
      else
	opts.mode=RAD;
    } else if (!strcmp(ext, ".nxi")) {
      opts.mode=NXI;
    } else if (!strcmp(ext, ".mc")) {
      opts.mode=MC;
    } else if (!strcmp(ext, ".mlt")) {
      opts.mode=MLT;
    } else if (fsize>=81920l) {
      if (fsize==81936l || fsize==81952l) {
	opts.mode=L2_640;
      } else {
	opts.mode=L2_320;
      }
    } else if (fsize>=49152l) {
      opts.mode=L2_256;
    } else if (fsize>=12288l) {
      if (fsize&0x01) {
	if (fsize==12289l || fsize==12353l) {
	  opts.mode=HIRES;
	} else {
	  opts.mode=HICOL;
	}
      } else {
	if (fsize==12544l || fsize==12800l) {
	  opts.mode=LORES;
	} else {
	  opts.mode=HICOL;
	}
      }
    } else if (fsize>=6912l) {
      opts.mode=ULA;
    } else if (fsize>=6144l) {
      opts.mode=LORES;
    } else {
      error(4, "Unable to guess mode", NULL);
    }
  }
  switch(opts.mode) {
  case RAD:
    palstyle=PALSTYLE_4;
    opts.imgsz=6144;
    /*
    opts.layer=LAYER1;
    opts.partord=IEP;
    opts.pixord=ORD_NATIVE;
    opts.attrord=ORD_NATIVE;
    */
    opts.desc=0x00;
    break;
  case ULA:
    palstyle=PALSTYLE_ULA;
    if (fsize<6912)
      opts.imgsz=6144;
    else
      opts.imgsz=6912;
    /*
    opts.layer=LAYER1;
    opts.partord=IEP;
    opts.pixord=ORD_NATIVE;
    opts.attrord=ORD_NATIVE;
    */
    opts.desc=0x00;
    break;
  case HIRES:
    palstyle=PALSTYLE_1;
    opts.imgsz=12288;
    /*
    opts.layer=LAYER1;
    opts.partord=IEP;
    opts.pixord=ORD_NATIVE;
    opts.attrord=ORD_NATIVE;
    */
    opts.desc=0x00;
    break;
  case HICOL:
    palstyle=PALSTYLE_ULA;
    opts.imgsz=12288;
    /*
    opts.layer=LAYER1;
    opts.partord=IEP;
    opts.pixord=ORD_NATIVE;
    opts.attrord=ORD_NATIVE;
    */
    opts.desc=0x00;
    break;
  case MC:
    palstyle=PALSTYLE_ULA;
    opts.imgsz=12288;
    /*
    opts.layer=LAYER1;
    opts.partord=IEP;
    opts.pixord=ORD_NORMAL;
    opts.attrord=ORD_NORMAL;
    */
    opts.desc=0x60;
    break;
  case MLT:
    palstyle=PALSTYLE_ULA;
    opts.imgsz=12288;
    /*
    opts.layer=LAYER1;
    opts.partord=IEP;
    opts.pixord=ORD_NATIVE;
    opts.attrord=ORD_NORMAL;
    */
    opts.desc=0x40;
    break;
  case LORES:
    palstyle=PALSTYLE_8;
    opts.imgsz=12288;
    /*
    opts.layer=LAYER1;
    opts.partord=IEP;
    opts.pixord=ORD_NATIVE;
    opts.attrord=ORD_NATIVE;
    */
    opts.desc=0x00;
    break;
  case L2_256:
    palstyle=PALSTYLE_8;
    opts.imgsz=49152l;
    /*
    opts.layer=LAYER2;
    opts.partord=IEP;
    opts.pixord=ORD_NATIVE;
    opts.attrord=ORD_NATIVE;
    */
    opts.desc=0x08;
    break;
  case NXI:
    palstyle=PALSTYLE_8;
    opts.imgsz=49152l;
    /*
    opts.layer=LAYER2;
    opts.partord=PEI;
    opts.pixord=ORD_NATIVE;
    opts.attrord=ORD_NATIVE;
    */
    opts.desc=0x18;
    break;
  case L2_320:
    palstyle=PALSTYLE_8;
    opts.imgsz=81920l;
    /*
    opts.layer=LAYER2;
    opts.partord=IEP;
    opts.pixord=ORD_NATIVE;
    opts.attrord=ORD_NATIVE;
    */
    opts.desc=0x08;
    break;
  case L2_640:
    palstyle=PALSTYLE_4;
    opts.imgsz=81920l;
    /*
    opts.layer=LAYER2;
    opts.partord=IEP;
    opts.pixord=ORD_NATIVE;
    opts.attrord=ORD_NATIVE;
    */
    opts.desc=0x08;
    break;
  }
  opts.extra=fsize&0x01;
  opts.palsz=fsize-opts.imgsz-opts.extra;
  switch(opts.palsz) {
  case 0:
    /*
    opts.paltype=PALTYPE_NONE;
    */
    opts.desc|=0x00;
    break;
  case 16: /* normal 8-bit, 16 colour */
  case 256: /* normal 8-bit, 256 colour */
    /*
    opts.paltype=PALTYPE_NORM;
    opts.palbits=PALBITS_8;
    */
    opts.desc|=0x03;
    break;
  case 32: /* normal 9-bit, 16 colour or ULANext 0b00001111, 8-bit */
    if (palstyle==PALSTYLE_4) {
      /*
      opts.paltype=PALTYPE_NORM;
      opts.palbits=PALBITS_9;
      */
      opts.desc|=0x07;
    } else {
      /*
      opts.paltype=PALTYPE_ULANEXT;
      opts.palbits=PALBITS_8;
      */
      opts.desc|=0x02;
    }
    break;
  case 40: /* ULANext 0b00000111/0b00011111, 8-bit */
  case 68: /* ULANext 0b00000011/0b00111111, 8-bit */
  case 130: /* ULANext 0b00000001/0b01111111, 8-bit */
    /*
    opts.paltype=PALTYPE_ULANEXT;
    opts.palbits=PALBITS_8;
    */
    opts.desc|=0x02;
    break;
  case 64: /* ULAplus or ULANext 0b00001111, 9-bit */
    if (opts.extra && palstyle==PALSTYLE_ULA) {
      /*
      opts.paltype=PALTYPE_ULANEXT;
      opts.palbits=PALBITS_9;
      */
      opts.desc|=0x06;
    } else
      /*
      opts.paltype=PALTYPE_ULAPLUS;
      */
      opts.desc|=0x01;
    break;
  case 80: /* ULANext 0b00000111/0b00011111, 9-bit */
  case 136: /* ULANext 0b00000011/0b00111111, 9-bit */
  case 260: /* ULANext 0b00000001/0b01111111, 9-bit */
    /*
    opts.paltype=PALTYPE_ULANEXT;
    opts.palbits=PALBITS_9;
    */
    opts.desc=0x06;
    break;
  case 258: /* ULANext 0b11111111, 8-bit */
    opts.extra=1;
    opts.palsz=257;
    /*
    opts.paltype=PALTYPE_ULANEXT;
    opts.palbits=PALBITS_8;
    */
    opts.desc|=02;
    break;
  case 512: /* normal 9-bit, 256 colour */
    /*
    opts.paltype=PALTYPE_NORM;
    opts.palbits=PALBITS_9;
    */
    opts.desc|=0x07;
    break;
  case 514:
    opts.extra=1;
    opts.palsz=513;
    /*
    opts.paltype=PALTYPE_ULANEXT;
    opts.palbits=PALBITS_9;
    */
    opts.desc|=0x06;
    break;
  default:
    error(7, "Bad palette", NULL);
  }
}

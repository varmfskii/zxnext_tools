#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arch/zxn/esxdos.h>
#include "showsimg.h"

void getopts(int argc, char *argv[]) {
  uint8_t i, j;
  struct esx_stat stat;
  
  opts.name=NULL;
  opts.ext=NULL;
  opts.mode=UNKNOWN;
  opts.size=0;
  opts.palette=0;
  opts.autoexit=0;
  opts.info=0;
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
	case 'R':
	  opts.mode = RAD;
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
	case 'n':
	  opts.mode = NXI;
	  break;
	case 'r':
	  opts.mode = HIRES;
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
      opts.ext = getext(opts.name);
    }
  }
  if (!opts.name) {
    help();
    error(7, "Bad command", NULL);
  }
  if (esx_f_stat(opts.name, &stat)==0xff)
    error(errno, "Unable to stat:", opts.name);
  opts.size=stat.size;
  if (opts.mode==UNKNOWN) {
    if (!strcmp(opts.ext, ".scr")) {
      opts.mode=ULA;
    } else if (!strcmp(opts.ext, ".shc")) {
      opts.mode=HICOL;
    } else if (!strcmp(opts.ext, ".shr")) {
      opts.mode=HIRES;
    } else if (!strcmp(opts.ext, ".sl2")) {
      if (opts.size==81920l || opts.size>81952l)
	opts.mode=L2_320;
      else if (opts.size>81920l)
	opts.mode=L2_640;
      else
	opts.mode=L2_256;
    } else if (!strcmp(opts.ext, ".slr")) {
      if (opts.size>=12288)
	opts.mode=LORES;
      else
	opts.mode=RAD;
    } else if (!strcmp(opts.ext, ".nxi")) {
      opts.mode=NXI;
    } else if (opts.size>=81920l) {
      if (opts.size==81936l || opts.size==81952l) {
	opts.mode=L2_640;
      } else {
	opts.mode=L2_320;
      }
    } else if (opts.size>=49152l) {
      opts.mode=L2_256;
    } else if (opts.size>=12288l) {
      if ((opts.extra=opts.size&0x01)) {
	if (opts.size==12289l || opts.size==12353l) {
	  opts.mode=HIRES;
	} else {
	  opts.mode=HICOL;
	}
      } else {
	if (opts.size==12544l || opts.size==12800l) {
	  opts.mode=LORES;
	} else {
	  opts.mode=HICOL;
	}
      }
    } else if (opts.size>=6912l) {
      opts.extra=opts.size&0x01;
      opts.mode=ULA;
    } else if (opts.size>=6144l) {
      opts.mode=LORES;
    } else {
      error(4, "Unable to guess mode", NULL);
    }
  }
  switch(opts.mode) {
  case RAD:
    opts.size-=6144;
    break;
  case ULA:
    opts.size-=6912+opts.extra;
    break;
  case HIRES:
  case HICOL:
    opts.size-=12288+opts.extra;
    break;
  case LORES:
    opts.size-=12288;
    break;
  case L2_256:
  case NXI:
    opts.size-=49152l;
    break;
  case L2_320:
  case L2_640:
    opts.size-=81920l;
    break;
  }
  switch(opts.size) {
  case 0:
    opts.palette=PNONE;
    break;
  case 16: /* normal 8-bit, 16 colour */
  case 256: /* normal 8-bit, 256 colour */
    opts.palette=P8|PNORM;
    break;
  case 32: /* normal 9-bit, 16 colour or ULANext 0b00001111, 8-bit */
    if (opts.mode&0x20)
      opts.palette=P9|PNORM;
    else
      opts.palette=P8|ULANEXT;
    break;
  case 40: /* ULANext 0b00000111/0b00011111, 8-bit */
  case 68: /* ULANext 0b00000011/0b00111111, 8-bit */
  case 130: /* ULANext 0b00000001/0b01111111, 8-bit */
    opts.palette=P8|ULANEXT;
    break;
  case 64: /* ULAplus or ULANext 0b00001111, 9-bit */
    if (opts.extra && opts.mode!=HIRES)
      opts.palette=P9|ULANEXT;
    else
      opts.palette=P8|ULAPLUS;
    break;
  case 80: /* ULANext 0b00000111/0b00011111, 9-bit */
  case 136: /* ULANext 0b00000011/0b00111111, 9-bit */
  case 260: /* ULANext 0b00000001/0b01111111, 9-bit */
    opts.palette=P9|ULANEXT;
    break;
  case 258: /* ULANext 0b11111111, 8-bit */
    opts.extra=1;
    opts.size=257;
    opts.palette=P8|ULANEXT;
    break;
  case 512: /* normal 9-bit, 256 colour */
    opts.palette=P9|PNORM;
    break;
  case 514:
    opts.extra=1;
    opts.size=513;
    opts.palette=P9|ULANEXT;
    break;
  default:
    error(7, "Bad palette", string32(opts.size));
  }
  if (opts.palette&PTYPE && opts.mode&0x20)
    error(7, "Incompatible palette mode", NULL);
}

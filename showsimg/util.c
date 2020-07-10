#include <stdio.h>
#include <stdlib.h>
#include "showsimg.h"

//static char num[12];

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

char *getopts(int argc, char *argv[]) {
  char *name=NULL;
  uint8_t i, j;
  
  opts.mode=UNKNOWN;
  opts.size=0;
  opts.palbits=0;
  opts.ulaplus=0;
  opts.autoexit=0;
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
	case '8':
	  opts.palbits = 8;
	  break;
	case '9':
	  opts.palbits = 9;
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
	case 'l':
	  opts.mode = LORES;
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
	case '+':
	  opts.ulaplus = 1;
	  break;
	default:
	  help();
	  error(7, "Unknown option", NULL);
	}
      }
    } else {
      name = argv[i];
    }
  }
  if (opts.ulaplus && opts.palbits) error(7, "Multiple palette modes", NULL);
  if (!(opts.mode&TIMEX) && opts.ulaplus)
    error(7, "Incompatible palette mode", NULL);
  if (!name) {
    help();
    error(7, "Bad command", NULL);
  }
  return name;
}

void help(void) {
  puts("Usage: .showsimg [<options>] <filename>");
  puts("options:");
  puts("\t-2: Layer 2 256x192x8");
  puts("\t-3: Layer 2 320x256x8");
  puts("\t-6: Layer 2 640x256x4");
  puts("\t-8: 8-bit palette entries");
  puts("\t-9: 9-bit palette entries");
  puts("\t-R: Radistan 128x96x4");
  puts("\t-l: LoRes 128x96x8");
  puts("\t-r: Timex HiRes 512x192x1");
  puts("\t-c: Timex HiCol 256x192/8x1");
  puts("\t-u: ULA 256x192/8x8");
  puts("\t-x: Do not wait, do not restore");
  puts("\t-+: ULA+");
}
/*
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
*/

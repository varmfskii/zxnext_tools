#include "ppmtolayer2.h"
#include "../support/support.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "1.0.0"
#define DATE "20190210"

void help(char *);
void version(void);

int main(int argc, char *argv[]) {
  int opt, ix;
  char *opts="hi:o:p:V";
  struct option options[]={
    { "help", 0, NULL, 'h' },
    { "in", 1, NULL, 'i' },
    { "out", 1, NULL, 'o' },
    { "pal", 1, NULL, 'p' },
    { "ver", 0, NULL, 'V' },
    { NULL, 0, NULL, '\0' }
  };
  FILE *infile, *outfile, *pin;
  rgb_t rgb;
  pal_t pal;
  ixed_t ixed;
    
  infile=stdin;
  outfile=stdout;
  pin=NULL;
  while((opt=getopt_long(argc, argv, opts, options, &ix))!=-1) {
    switch(opt) {
    case 'h':
      help(argv[0]);
      exit(0);
    case 'i':
      if(!(infile=fopen(optarg, "r"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
      break;
    case 'o':
      if(!(outfile=fopen(optarg, "w"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
      break;
    case 'p':
      if(!(pin=fopen(optarg, "r"))) {
	fprintf(stderr, "Unable to open %s\n", optarg);
	return 1;
      }
    case 'V':
      version();
      exit(0);
    default:
      fprintf(stderr, "Illegal option %c\n", opt);
      help(argv[0]);
      exit(1);
    }
  }
  if (infile==stdin && argc>1) 
      if(!(infile=fopen(argv[1], "r"))) {
	fprintf(stderr, "Unable to open %s\n", argv[1]);
	return 1;
      }
  if (infile==stdin && argc>2) 
      if(!(infile=fopen(argv[2], "r"))) {
	fprintf(stderr, "Unable to open %s\n", argv[2]);
	return 1;
      }
  rgb=readppm(infile);
  if (pin) {
    pal=readpal(0x100, pin);
    fclose(pin);
    fwrite(pal.dat, 0x200, 1, outfile);
  }  else
    pal=palette(8);
  ixed=rgb2index(rgb, pal, 0, 0, 1, 1);
  free(rgb.dat);
  free(pal.dat);
  writelayer2(ixed, outfile);
  free(ixed.dat);
  fclose(outfile);
  return 0;
}

void help(char *name) {
  version();
  fprintf(stderr, "Usage: %s [<options>] [<infile> [<outfile>]]\n", name);
  fprintf(stderr, "\toptions are\n");
  fprintf(stderr, "\t-h\t--help\tprint this help message\n");
  fprintf(stderr, "\t-i\t--in\tinput file (stdin)\n");
  fprintf(stderr, "\t-o\t--out\toutput file (stdout)\n");
  fprintf(stderr, "\t-p\t--pal\tpalette file (iinternal)\n");
  fprintf(stderr, "\t-V\t--ver\tget version information\n");
}

void version(void) {
  fprintf(stderr, "ppmtolayer2 version %s %s\n", VERSION, DATE);
}
